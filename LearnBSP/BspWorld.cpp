/*
 * Learn BSP is a sample source code to see how a Half-Life level file
 * can be used in your 3D application
 * Copyright (C) 2009  Wouter Saaltink

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BspWorld.h"
#include "common/tokenizer.h"
#include "PluginManager.h"
#include <iostream>
#include <string.h>

/*!
 * \brief
 */
BspWorld::BspWorld()
    : mLeafCount(0), mLeafs(NULL), mNodeCount(0), mNodes(NULL), mFaceCount(0), mFaces(NULL),
        mModelCount(0), mModels(NULL), mTextureCount(0), mTextures(NULL), mWorldEntity(NULL),
        mVertexIndices(NULL), mTextureUV(NULL), mLightmapUV(NULL),
        mTitle(NULL), mSkyName(NULL), mWad(NULL), mWaveHeight(5), mMaxRange(4096)
{
}

/*!
 * \brief
 */
BspWorld::~BspWorld() 
{
    close();
}

/*!
 * \brief
 * \param data
 * \return 
 */
bool BspWorld::open(const Data& data, TextureLoader& textureLoader)
{
    if (!BspData::testBSP(data))
        return false;

    BspData bsp(data);

    // Load the data structtures from the BSP file
    this->mNodeCount = bsp.nodeCount;
    this->mLeafCount = bsp.leafCount;
    this->mFaceCount = bsp.faceCount;
    this->mModelCount = bsp.modelCount;
    this->mTextureCount = ((int*)bsp.textureData)[0];

    // Create the Object instances fro nodes, leafs and faces
    this->mNodes = new BspNode[this->mNodeCount];
    this->mLeafs = new BspLeaf[this->mLeafCount];
    this->mFaces = new BspFace[this->mFaceCount];
    this->mModels = new BspModel[this->mModelCount];
    this->mTextures = new Texture[this->mTextureCount];

    // Setup the index arrays
    this->mVertexIndices = new IndexArray<3>;
    this->mTextureUV = new IndexArray<2>;
    this->mLightmapUV = new IndexArray<2>;

    if (!parseEntityData(bsp, textureLoader))
        return false;

    if (!parseTextures(bsp, textureLoader))
        return false;

    if (!parseNodes(bsp))
        return false;

    if (!parseLeafs(bsp))
        return false;

    if (!parseFaces(bsp))
        return false;

    if (!parseModels(bsp))
        return false;

    if (!setupEntities())
        return false;

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, *this->mVertexIndices);

    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, *this->mTextureUV);

    glClientActiveTexture(GL_TEXTURE1);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, *this->mLightmapUV);

    return true;
}

/*!
 * \brief
 * \param bsp
 * \return
 */
bool BspWorld::parseEntityData(BspData& bsp, TextureLoader& textureLoader)
{
    Tokenizer tok(bsp.entityData, bsp.entitySize);

    while (tok.nextToken() && strcmp(tok.getToken(), "{") == 0)
    {
        // Parse the entity data into the entity instance
        BspEntity* entity = new BspEntity();
        if (!entity->parseFromTokenizer(tok))
            return false;

        // Check the classname for special cases entities like the worldspawn
        const char* classname = entity->getClassName();
        if (strcasecmp(classname, "worldspawn") == 0)
        {
            this->setWorldEntity(entity);
            textureLoader.setWadFiles(entity->getValue("wad"));
        }

        // Add the entity to the entity list
        this->mEntities.push_back(entity);
    }
    return true;
}

/*!
 * \brief
 * \param bsp
 * \return
 */
bool BspWorld::parseTextures(BspData& bsp, TextureLoader& textureLoader)
{
    // Save the texture index table with in the first place the number of textures so this one is skipped
    int* table = (int*)bsp.textureData;

    glActiveTexture(GL_TEXTURE0);
    for (int t = 0; t < this->mTextureCount; t++)
    {
        // Load texture with the texture loader and upload it to GL
        textureLoader.loadMiptexTexture(this->mTextures[t], bsp.textureData + table[t + 1]);
        this->mTextures[t].upload();
    }

    return true;
}

/*!
 * \brief
 * \param bsp
 * \return
 */
bool BspWorld::parseNodes(BspData& bsp)
{
    for (int n = 0; n < this->mNodeCount; n++)
    {
        tBSPNode& node = bsp.nodes[n];
        tBSPPlane& plane = bsp.planes[node.planeIndex];
        this->mNodes[n].index = n;
        this->mNodes[n].setPlane(plane.normal, plane.distance);
        this->mNodes[n].setBoundingBox(BoundingBox(node.mins, node.maxs));
        BspNode* front = NULL;
        BspNode* back = NULL;
        if (node.children[0] >= 0)
            front = &this->mNodes[node.children[0]];
        else
        {
            BspLeaf* leaf = &this->mLeafs[-(node.children[0] + 1)];
            front = new BspNode(leaf);
        }
        if (node.children[1] >= 0)
            back = &this->mNodes[node.children[1]];
        else
        {
            BspLeaf* leaf = &this->mLeafs[-(node.children[1] + 1)];
            back = new BspNode(leaf);
        }
        this->mNodes[n].setChildren(front, back);
    }
    return true;
}

/*!
 * \brief
 * \param bsp
 * \return
 */
bool BspWorld::parseLeafs(BspData& bsp)
{
    for (int l = 1; l < this->mLeafCount; l++)
    {
        tBSPLeaf& leaf = bsp.leafs[l];
        this->mLeafs[l].index = l;
        this->mLeafs[l].setBoundingBox(BoundingBox(leaf.mins, leaf.maxs));
        for (int f = 0; f < leaf.markSurfacesCount; f++)
        {
            int faceIndex = bsp.marksurfaces[leaf.firstMarkSurface + f];
            this->mLeafs[l].addFace(&this->mFaces[faceIndex]);
        }

        // Decompress visibility data
        int visibilityOffset = bsp.leafs[l].visiblityOffset;
        for (int j = 1; j < bsp.models[0].visLeafCount; visibilityOffset++)
        {
            if (bsp.visibilityData[visibilityOffset] == 0)
            {
                visibilityOffset++;
                j += (bsp.visibilityData[visibilityOffset]<<3);
            }
            else
            {
                for (unsigned char bit = 1; bit; bit<<=1, j++)
                {
                    if (bsp.visibilityData[visibilityOffset] & bit)
                        this->mLeafs[l].addVisibleLeaf(&this->mLeafs[j]);
                }
            }
        }
    }
    return true;
}

/*!
 * \brief
 * \param bsp
 * \return
 */
bool BspWorld::parseFaces(BspData& bsp)
{
    for (int f = 0; f < this->mFaceCount; f++)
    {
        tBSPFace& face = bsp.faces[f];
        tBSPPlane& plane = bsp.planes[face.planeIndex];
        tBSPTexInfo& texinfo = bsp.texinfos[face.texinfoIndex];
        Texture* texture = &this->mTextures[texinfo.miptexIndex];
        this->mFaces[f].setPlane(plane.normal, plane.distance);
        this->mFaces[f].setVertices(this->mVertexIndices->current(), face.edgeCount);
        this->mFaces[f].setFlags(texinfo.flags);
        this->mFaces[f].setTexture(texture);

        float is = 1.0f / float(texture->width);
        float it = 1.0f / float(texture->height);
        float min[2], max[2];
        this->getFaceBounds(face, texinfo, bsp, min, max);
        const Texture* lightmap = this->mFaces[f].setLightmap(face, min, max, bsp.lightingData);
        
        for (int e = 0; e < face.edgeCount; e++)
        {
            float vertex[3] = { 0 };
            float st[2] = { 0 };
            float lslt[2] = { 0 };
            int edgeIndex = bsp.surfedges[face.firstEdge + e];
            if (edgeIndex < 0)
            {
                const tBSPEdge& edge = bsp.edges[-edgeIndex];
                vertex[0] = bsp.vertices[edge.vertex[1]].point[0];
                vertex[1] = bsp.vertices[edge.vertex[1]].point[1];
                vertex[2] = bsp.vertices[edge.vertex[1]].point[2];
            }
            else
            {
                const tBSPEdge& edge = bsp.edges[edgeIndex];
                vertex[0] = bsp.vertices[edge.vertex[0]].point[0];
                vertex[1] = bsp.vertices[edge.vertex[0]].point[1];
                vertex[2] = bsp.vertices[edge.vertex[0]].point[2];
            }

            float s = DotProduct(vertex, texinfo.vecs[0]) + texinfo.vecs[0][3];
            float t = DotProduct(vertex, texinfo.vecs[1]) + texinfo.vecs[1][3];

            // Compute the texture coordinates
            st[0] = s * is;
            st[1] = t * it;

            // Compute the lightmap texture coordinates
            float midPolyS = (min[0] + max[0])/2.0f;
            float midPolyT = (min[1] + max[1])/2.0f;
            float midTexS = float(lightmap->width) / 2.0f;
            float midTexT = float(lightmap->height) / 2.0f;
            lslt[0] = (midTexS + (s - midPolyS) / 16.0f) / float(lightmap->width);
            lslt[1] = (midTexT + (t - midPolyT) / 16.0f) / float(lightmap->height);

            this->mVertexIndices->add(vertex);
            this->mTextureUV->add(st);
            this->mLightmapUV->add(lslt);
        }
    }
    return true;
}

/*!
 * \brief
 * \param bsp
 * \return
 */
bool BspWorld::parseModels(BspData& bsp)
{
    for (int m = 0; m < bsp.modelCount; m++)
    {
        tBSPModel& model = bsp.models[m];
        this->mModels[m].setHeadNode(&this->mNodes[model.headnode[0]]);
        this->mModels[m].setBoundingBox(BoundingBox(model.mins, model.maxs));
        for (int f = 0; f < model.faceCount; f++)
        {
            this->mModels[m].addFace(&this->mFaces[model.firstFace + f]);
        }
    }
    this->mHeadNode = &this->mNodes[bsp.models[0].headnode[0]];
    return true;
}

/*!
 * \brief
 * \return
 */
bool BspWorld::setupEntities()
{
    for (std::vector<BspEntity*>::const_iterator itr = this->mEntities.begin(); itr != this->mEntities.end(); ++itr)
    {
        const BspEntity* entity = *itr;
        const char* classname = entity->getClassName();
        BspObject* object = PluginManager::Instance()->getEntityInstance(classname, entity->getValues());
        if (object != NULL)
        {
            const BspMesh* mesh = object->getMesh();
            if (mesh != NULL)
            {
                float mins[3], maxs[3];
                mesh->getBoundingBox(mins, maxs);
                BoundingBox bb;
                bb.addPoint(mins);
                bb.addPoint(maxs);
                this->mHeadNode->addObject(object, bb);
            }
        }
    }
    return true;
}

/*!
 * \brief
 * \param camera
 */
void BspWorld::setCamera(Camera* camera)
{
    this->mCamera = camera;
}

/*!
 * \brief
 */
void BspWorld::render()
{
    const BspLeaf* leaf = this->mHeadNode->getLeaf(mCamera->getPosition());
    static const BspLeaf* lastLeaf = leaf;

    if (lastLeaf != leaf)
    {
        this->mRenderModels.clear();
        // ToDo: fix this to support BspObjects instead of BspModels. Then add line here to gather Objects
    }

    if (leaf->getFaceCount() > 0)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        this->mHeadNode->render(mCamera->getPosition());
    }
    else
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        this->mHeadNode->render();
    }

    for (std::set<BspModel*>::const_iterator model = this->mRenderModels.begin(); model != this->mRenderModels.end(); ++model)
    {
        (*model)->render();
    }

}

/*!
 * \brief
 */
void BspWorld::renderAllFaces() const
{
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int f = 1; f < this->mFaceCount; f++)
    {
        this->mFaces[f].render();
    }
}

/*!
 * \brief
 */
void BspWorld::close()
{
    if (this->mNodes != NULL)
        delete []this->mNodes;
    this->mNodes = NULL;
    this->mNodeCount = 0;

    if (this->mLeafs != NULL)
        delete []this->mLeafs;
    this->mLeafs = NULL;
    this->mLeafCount = 0;

    if (this->mFaces != NULL)
        delete []this->mFaces;
    this->mFaces = NULL;
    this->mFaceCount = 0;

    if (this->mModels != NULL)
        delete []this->mModels;
    this->mModels = NULL;
    this->mModelCount = 0;

    if (this->mTextures != NULL)
        delete []this->mTextures;
    this->mTextures = NULL;
    this->mTextureCount = 0;

    if (this->mVertexIndices != NULL)
        delete this->mVertexIndices;
    this->mVertexIndices = NULL;

    if (this->mTextureUV != NULL)
        delete this->mTextureUV;
    this->mTextureUV = NULL;

    if (this->mLightmapUV != NULL)
        delete this->mLightmapUV;
    this->mLightmapUV = NULL;

    while (!this->mEntities.empty())
    {
        BspEntity* entity = this->mEntities.back();
        this->mEntities.pop_back();
        delete entity;
    }
}

/*!
 * \brief
 * \param world
 */
void BspWorld::setWorldEntity(BspEntity* world)
{
    const char* wad = world->getValue("wad");
    if (wad != NULL)
    {
        this->mWad = new char[strlen(wad) + 1];
        strcpy(this->mWad, wad);
    }
    else
    {
        this->mWad = new char[9];
        strcpy(this->mWad, "zhlt.wad");
    }

    const char* chaptertitle = world->getValue("chaptertitle");
    if (chaptertitle != NULL)
    {
        this->mWad = new char[strlen(chaptertitle) + 1];
        strcpy(this->mWad, chaptertitle);
    }
    else
    {
        this->mWad = new char[9];
        strcpy(this->mWad, "No Title");
    }

    const char* skyname = world->getValue("skyname");
    if (skyname != NULL)
    {
        this->mSkyName = new char[strlen(wad) + 1];
        strcpy(this->mSkyName, skyname);
    }
    else
    {
        this->mWad = new char[5];
        strcpy(this->mWad, "dusk");
    }

    const char* waveheight = world->getValue("WaveHeight");
    if (waveheight != NULL)
    {
        this->mWaveHeight = atoi(waveheight);
    }

    const char* maxrange = world->getValue("MaxRange");
    if (maxrange != NULL)
    {
        this->mWaveHeight = atoi(maxrange);
    }
}

/*!
 * \brief
 * \param bspFace
 * \param texinfo
 * \param surfedges
 * \param edges
 * \param vertices
 * \param min
 * \param max
 */
void BspWorld::getFaceBounds(const tBSPFace& bspFace, const tBSPTexInfo& texinfo, BspData& bsp, float min[2], float max[2])
{
    min[0] = min[1] =  999999;
    max[0] = max[1] = -999999;
    
    for (int e = 0; e < bspFace.edgeCount; e++)
    {
        const tBSPVertex* vertex = NULL;
        int edgeIndex = bsp.surfedges[bspFace.firstEdge + e];
        if (edgeIndex >= 0)
            vertex = &bsp.vertices[bsp.edges[edgeIndex].vertex[0]];
        else
            vertex = &bsp.vertices[bsp.edges[-edgeIndex].vertex[1]];

        for (int j = 0; j < 2 ; j++)
        {
            float value =  (vertex->point[0] * texinfo.vecs[j][0]) +
                        (vertex->point[1] * texinfo.vecs[j][1]) +
                        (vertex->point[2] * texinfo.vecs[j][2]) +
                        texinfo.vecs[j][3];

            if (value < min[j]) min[j] = value;
            if (value > max[j])  max[j] = value;
        }
    }
}

/*!
 * \brief
 * \return
 */
const char* BspWorld::getTitle() const
{
    return this->mTitle;
}

/*!
 * \brief
 * \return
 */
const char* BspWorld::getSkyName() const
{
    return this->mSkyName;
}

/*!
 * \brief
 * \return
 */
const char* BspWorld::getWad() const
{
    return this->mWad;
}

/*!
 * \brief
 * \return
 */
int BspWorld::getWaveHeight() const
{
    return this->mWaveHeight;
}

/*!
 * \brief
 * \return
 */
int BspWorld::getMaxRange() const
{
    return this->mMaxRange;
}
