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
#include <iostream>

/*!
 * \brief
 */
BspWorld::BspWorld()
    : mLeafCount(0), mLeafs(NULL), mNodeCount(0), mNodes(NULL), mFaceCount(0), mFaces(NULL),
        mModelCount(0), mModels(NULL), mVertexIndices(NULL), mTextureUV(NULL), mLightmapUV(NULL)
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
bool BspWorld::open(const Data& data)
{
    tBSPHeader header;
    tBSPPlane* planes = NULL;

    if (!this->testFile(data, header))
        return false;

    // Load the data structtures from the BSP file
    this->loadLump(&planes, header.lumps[HL1_BSP_PLANELUMP], &data);
    this->mNodeCount = header.lumps[HL1_BSP_NODELUMP].size / sizeof(tBSPNode);
    this->mLeafCount = header.lumps[HL1_BSP_LEAFLUMP].size / sizeof(tBSPLeaf);
    this->mFaceCount = header.lumps[HL1_BSP_FACELUMP].size / sizeof(tBSPFace);
    this->mModelCount = this->loadLump(&this->mModels, header.lumps[HL1_BSP_MODELLUMP], &data);

    // Create the Object instances fro nodes, leafs and faces
    this->mNodes = new BspNode[this->mNodeCount];
    this->mLeafs = new BspLeaf[this->mLeafCount];
    this->mFaces = new BspFace[this->mFaceCount];

    // Setup the index arrays
    this->mVertexIndices = new IndexArray<3>;
    this->mTextureUV = new IndexArray<2>;
    this->mLightmapUV = new IndexArray<2>;

    // Parse the leafs
    {
        tBSPLeaf* leafs = NULL;
        tBSPModel* models = NULL;
        unsigned short* marksurfaces = NULL;
        unsigned char* visibility = NULL;

        this->loadLump(&leafs, header.lumps[HL1_BSP_LEAFLUMP], &data);
        this->loadLump(&marksurfaces, header.lumps[HL1_BSP_MARKSURFACELUMP], &data);
        this->loadLump(&visibility, header.lumps[HL1_BSP_VISIBILITYLUMP], &data);
        this->loadLump(&models, header.lumps[HL1_BSP_MODELLUMP], &data);

        for (int l = 1; l < this->mLeafCount; l++)
        {
            tBSPLeaf& leaf = leafs[l];
            this->mLeafs[l].index = l;
            this->mLeafs[l].setFaceCount(leaf.markSurfacesCount);
            for (int f = 0; f < leaf.markSurfacesCount; f++)
            {
                int faceIndex = marksurfaces[leaf.firstMarkSurface + f];
                this->mLeafs[l].setFace(&this->mFaces[faceIndex], f);
            }

            // Decompress visibility data
            int visibilityOffset = leafs[l].visiblityOffset;
            for (int j = 1; j < models[0].visLeafCount; visibilityOffset++)
            {
                if (visibility[visibilityOffset] == 0)
                {
                    visibilityOffset++;
                    j += (visibility[visibilityOffset]<<3);
                }
                else
                {
                    for (unsigned char bit = 1; bit; bit<<=1, j++)
                    {
                        if (visibility[visibilityOffset] & bit)
                            this->mLeafs[l].addVisibleLeaf(&this->mLeafs[j]);
                    }
                }
            }
        }

        if (leafs != NULL) delete []leafs;
        if (models != NULL) delete []models;
        if (marksurfaces != NULL) delete []marksurfaces;
        if (visibility != NULL) delete []visibility;
    }

    // Parse the nodes
    {
        tBSPNode *nodes = NULL;

        this->loadLump(&nodes, header.lumps[HL1_BSP_NODELUMP], &data);

        for (int n = 0; n < this->mNodeCount; n++)
        {
            tBSPNode& node = nodes[n];
            tBSPPlane& plane = planes[node.planeIndex];
            this->mNodes[n].index = n;
            this->mNodes[n].setPlane(plane.normal, plane.distance);
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

        if (nodes != NULL) delete []nodes;
    }

    // Parse faces
    {
        tBSPFace* faces = NULL;
        tBSPTexInfo* texinfos = NULL;
        tBSPEdge* edges = NULL;
        tBSPVertex* vertices = NULL;
        int * surfedges = NULL;

        this->loadLump(&faces, header.lumps[HL1_BSP_FACELUMP], &data);
        this->loadLump(&texinfos, header.lumps[HL1_BSP_TEXINFOLUMP], &data);
        this->loadLump(&edges, header.lumps[HL1_BSP_EDGELUMP], &data);
        this->loadLump(&vertices, header.lumps[HL1_BSP_VERTEXLUMP], &data);
        this->loadLump(&surfedges, header.lumps[HL1_BSP_SURFEDGELUMP], &data);

        for (int f = 0; f < this->mFaceCount; f++)
        {
            tBSPFace& face = faces[f];
            tBSPPlane& plane = planes[face.planeIndex];
            tBSPTexInfo& texinfo = texinfos[face.texinfoIndex];
            this->mFaces[f].setPlane(plane.normal, plane.distance);
            this->mFaces[f].setVertices(this->mVertexIndices->current(), face.edgeCount);
            this->mFaces[f].setFlags(texinfo.flags);

            for (int e = 0; e < face.edgeCount; e++)
            {
                float vertex[3] = { 0 };
                int edgeIndex = surfedges[face.firstEdge + e];
                if (edgeIndex < 0)
                {
                    const tBSPEdge& edge = edges[-edgeIndex];
                    vertex[0] = vertices[edge.vertex[1]].point[0];
                    vertex[1] = vertices[edge.vertex[1]].point[1];
                    vertex[2] = vertices[edge.vertex[1]].point[2];
                }
                else
                {
                    const tBSPEdge& edge = edges[edgeIndex];
                    vertex[0] = vertices[edge.vertex[0]].point[0];
                    vertex[1] = vertices[edge.vertex[0]].point[1];
                    vertex[2] = vertices[edge.vertex[0]].point[2];
                }
                this->mVertexIndices->add(vertex);
            }
        }

        if (faces != NULL) delete []faces;
        if (texinfos != NULL) delete []texinfos;
        if (edges != NULL) delete []edges;
        if (vertices != NULL) delete []vertices;
        if (surfedges != NULL) delete []surfedges;
    }

    if (planes != NULL) delete []planes;

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, *this->mVertexIndices);

    return true;
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
 * \param position
 * \param model
 * \return
 */
const BspLeaf* BspWorld::getLeaf(const float position[3], int model) const
{
    if (model < 0 || model >= this->mModelCount)
        return NULL;
    
    const BspNode* node = &this->mNodes[this->mModels[model].headnode[0]];
    const BspNode* child = node->getChild(position);

    while (child != NULL)
    {
        node = child;
        child = node->getChild(position);
    }
    return node->getLeaf();
}

/*!
 * \brief
 * \param model
 */
const BspNode* BspWorld::getHeadNode(int model) const
{
    return &this->mNodes[this->mModels[model].headnode[0]];
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

    delete this->mVertexIndices;
    delete this->mTextureUV;
    delete this->mLightmapUV;
}

/*!
 * \brief
 * \param file
 * \param header
 * \return
 */
bool BspWorld::testFile(const Data& file, tBSPHeader& header)
{
    if (!file.read(&header)) {
        std::cout << "Could not read the BSP header" << std::endl;
        return false;
    }

    if (header.signature != HL1_BSP_SIGNATURE) {
        std::cout << "Wrong BSP signature" << std::endl;
        return false;
    }

    if (header.lumps[HL1_BSP_PLANELUMP].size % sizeof(tBSPPlane) != 0)
    {
        std::cout << "Plane lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_VERTEXLUMP].size % sizeof(tBSPVertex) != 0)
    {
        std::cout << "Vertex lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_NODELUMP].size % sizeof(tBSPNode) != 0)
    {
        std::cout << " Node lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_TEXINFOLUMP].size % sizeof(tBSPTexInfo) != 0)
    {
        std::cout << "Texture info lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_FACELUMP].size % sizeof(tBSPFace) != 0)
    {
        std::cout << "Face lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_CLIPNODELUMP].size % sizeof(tBSPClipNode) != 0)
    {
        std::cout << "Clipnode lump has the wrond size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_LEAFLUMP].size % sizeof(tBSPLeaf) != 0)
    {
        std::cout << "Leaf lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_EDGELUMP].size % sizeof(tBSPEdge) != 0)
    {
        std::cout << "Edge lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_MODELLUMP].size % sizeof(tBSPModel) != 0)
    {
        std::cout << "Model lump has the wrond size" << std::endl;
        return false;
    }
    
    return true;
}

