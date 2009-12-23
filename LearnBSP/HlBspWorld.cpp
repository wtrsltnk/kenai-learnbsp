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

#include "HlBspWorld.h"
#include <stdio.h>
#include <string.h>

HlBspWorld::HlBspWorld()
	: BspWorld(), mTitle(NULL), mSkyName(NULL), mWad(NULL), mWaveHeight(5), mMaxRange(4096)
{
}

HlBspWorld::~HlBspWorld()
{
}

bool HlBspWorld::onOpen(const Data& data, TextureLoader& textureLoader)
{
    if (!HlBspData::testBSP(data))
        return false;

    HlBspData bsp(data);

    // Load the data structtures from the BSP file
    this->mLeafCount = bsp.leafCount;
    this->mFaceCount = bsp.faceCount;
    this->mModelCount = bsp.modelCount;
    this->mTextureCount = ((int*)bsp.textureData)[0];

    // Create the Object instances fro nodes, leafs and faces
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

    if (!parseLeafs(bsp))
        return false;

    if (!parseFaces(bsp))
        return false;

    if (!parseModels(bsp))
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
bool HlBspWorld::parseEntityData(HlBspData& bsp, TextureLoader& textureLoader)
{
    Tokenizer tok(bsp.entityData, bsp.entitySize);

    while (tok.nextToken() && strcmp(tok.getToken(), "{") == 0)
    {
        // Parse the entity data into the entity instance
        BspEntity* entity = new BspEntity();
        if (entity->parseFromTokenizer(tok))
		{
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
    }
    return true;
}

/*!
 * \brief
 * \param bsp
 * \return
 */
bool HlBspWorld::parseTextures(HlBspData& bsp, TextureLoader& textureLoader)
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
bool HlBspWorld::parseLeafs(HlBspData& bsp)
{
    for (int l = 1; l < this->mLeafCount; l++)
    {
        hl::tBSPLeaf& leaf = bsp.leafs[l];
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
bool HlBspWorld::parseFaces(HlBspData& bsp)
{
    for (int f = 0; f < this->mFaceCount; f++)
    {
        hl::tBSPFace& face = bsp.faces[f];
        hl::tBSPPlane& plane = bsp.planes[face.planeIndex];
        hl::tBSPTexInfo& texinfo = bsp.texinfos[face.texinfoIndex];
        Texture* texture = &this->mTextures[texinfo.miptexIndex];
        this->mFaces[f].setPlane(plane.normal, plane.distance);
        this->mFaces[f].setVertices(this->mVertexIndices->current(), face.edgeCount);
        this->mFaces[f].setFlags(texinfo.flags);
        this->mFaces[f].setTexture(texture);

        float is = 1.0f / float(texture->width);
        float it = 1.0f / float(texture->height);
        float min[2], max[2];
        HlBspWorld::getFaceBounds(face, texinfo, bsp, min, max);
        const Texture* lightmap = this->mFaces[f].setLightmap(face, min, max, bsp.lightingData);

        for (int e = 0; e < face.edgeCount; e++)
        {
            float vertex[3] = { 0 };
            float st[2] = { 0 };
            float lslt[2] = { 0 };
            int edgeIndex = bsp.surfedges[face.firstEdge + e];
            if (edgeIndex < 0)
            {
                const hl::tBSPEdge& edge = bsp.edges[-edgeIndex];
                vertex[0] = bsp.vertices[edge.vertex[1]].point[0];
                vertex[1] = bsp.vertices[edge.vertex[1]].point[1];
                vertex[2] = bsp.vertices[edge.vertex[1]].point[2];
            }
            else
            {
                const hl::tBSPEdge& edge = bsp.edges[edgeIndex];
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
bool HlBspWorld::parseModels(HlBspData& bsp)
{
    for (int m = 0; m < bsp.modelCount; m++)
    {
        hl::tBSPModel& model = bsp.models[m];
        this->mModels[m].setHeadNode(createNode(bsp.nodes[model.headnode[0]], model, bsp));
        this->mModels[m].setBoundingBox(BoundingBox(model.mins, model.maxs));
        for (int f = 0; f < model.faceCount; f++)
        {
            this->mModels[m].addFace(&this->mFaces[model.firstFace + f]);
        }
    }
    this->mHeadNode = this->mModels[0].getHeadNode();
    return true;
}

/*!
 * \brief
 * \param node
 * \param bsp
 * \return
 */
BspNode* HlBspWorld::createNode(const hl::tBSPNode& node, const hl::tBSPModel& model, HlBspData& bsp)
{
    BspNode* result = new BspNode();

    // Setup front and back node
    BspNode* front = NULL;
    BspNode* back = NULL;
    if (node.children[0] > 0)
        front = createNode(bsp.nodes[node.children[0]], model, bsp);
    else
        front = &this->mLeafs[-(node.children[0] + 1)];

    if (node.children[1] > 0)
        back = createNode(bsp.nodes[node.children[1]], model, bsp);
    else
        back = &this->mLeafs[-(node.children[1] + 1)];

    result->setChildren(front, back);

    // Setup splitting plane
    const hl::tBSPPlane& plane = bsp.planes[node.planeIndex];
    result->setPlane(plane.normal, plane.distance);

    // Setup bounding box
    BoundingBox bb = BoundingBox(node.mins, node.maxs);
    result->setBoundingBox(bb);

    return result;
}

/*!
 * \brief
 * \param world
 */
void HlBspWorld::setWorldEntity(BspEntity* world)
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
void HlBspWorld::getFaceBounds(const hl::tBSPFace& bspFace, const hl::tBSPTexInfo& texinfo, HlBspData& bsp, float min[2], float max[2])
{
    min[0] = min[1] =  999999;
    max[0] = max[1] = -999999;

    for (int e = 0; e < bspFace.edgeCount; e++)
    {
        const hl::tBSPVertex* vertex = NULL;
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
const char* HlBspWorld::getTitle() const
{
    return this->mTitle;
}

/*!
 * \brief
 * \return
 */
const char* HlBspWorld::getSkyName() const
{
    return this->mSkyName;
}

/*!
 * \brief
 * \return
 */
const char* HlBspWorld::getWad() const
{
    return this->mWad;
}

/*!
 * \brief
 * \return
 */
int HlBspWorld::getWaveHeight() const
{
    return this->mWaveHeight;
}

/*!
 * \brief
 * \return
 */
int HlBspWorld::getMaxRange() const
{
    return this->mMaxRange;
}

