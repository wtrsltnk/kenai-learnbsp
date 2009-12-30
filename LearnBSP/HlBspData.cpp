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

#include "HlBspData.h"
#include <iostream>

/*!
 * \brief
 * \param data
 */
HlBspData::HlBspData(const Data& data)
    : fs::Resource(fs::HlBspResource, data.name), entitySize(0), entityData(NULL), planeCount(0), planes(NULL), textureSize(0), textureData(NULL), vertexCount(0), vertices(NULL),
        visibilitySize(0), visibilityData(NULL), nodeCount(0), nodes(NULL), texinfoCount(0), texinfos(NULL), faceCount(0), faces(NULL),
        lightingSize(0), lightingData(NULL), clipnodeCount(0), clipnodes(NULL), leafCount(0), leafs(NULL), marksurfaceCount(0), marksurfaces(NULL),
        edgeCount(0), edges(NULL), surfedgeCount(0), surfedges(NULL), modelCount(0), models(NULL)
{
    hl::tBSPHeader header;
    
    if (!data.read(&header)) {
        std::cout << "Could not read the BSP header" << std::endl;
        return;
    }

    if (header.signature != HL1_BSP_SIGNATURE) {
        std::cout << "Wrong BSP signature" << std::endl;
        return;
    }

    this->entitySize = loadLump(&this->entityData, header.lumps[HL1_BSP_ENTITYLUMP], &data);
    this->planeCount = loadLump(&this->planes, header.lumps[HL1_BSP_PLANELUMP], &data);
    this->textureSize = loadLump(&this->textureData, header.lumps[HL1_BSP_TEXTURELUMP], &data);
    this->vertexCount = loadLump(&this->vertices, header.lumps[HL1_BSP_VERTEXLUMP], &data);
    this->visibilitySize = loadLump(&this->visibilityData, header.lumps[HL1_BSP_VISIBILITYLUMP], &data);
    this->nodeCount = loadLump(&this->nodes, header.lumps[HL1_BSP_NODELUMP], &data);
    this->texinfoCount = loadLump(&this->texinfos, header.lumps[HL1_BSP_TEXINFOLUMP], &data);
    this->faceCount = loadLump(&this->faces, header.lumps[HL1_BSP_FACELUMP], &data);
    this->lightingSize = loadLump(&this->lightingData, header.lumps[HL1_BSP_LIGHTINGLUMP], &data);
    this->clipnodeCount = loadLump(&this->clipnodes, header.lumps[HL1_BSP_CLIPNODELUMP], &data);
    this->leafCount = loadLump(&this->leafs, header.lumps[HL1_BSP_LEAFLUMP], &data);
    this->marksurfaceCount = loadLump(&this->marksurfaces, header.lumps[HL1_BSP_MARKSURFACELUMP], &data);
    this->edgeCount = loadLump(&this->edges, header.lumps[HL1_BSP_EDGELUMP], &data);
    this->surfedgeCount = loadLump(&this->surfedges, header.lumps[HL1_BSP_SURFEDGELUMP], &data);
    this->modelCount = loadLump(&this->models, header.lumps[HL1_BSP_MODELLUMP], &data);
}

/*!
 * \brief
 */
HlBspData::~HlBspData()
{
    if (entityData) delete []entityData;
    if (planes) delete []planes;
    if (textureData) delete []textureData;
    if (vertices) delete []vertices;
    if (visibilityData) delete []visibilityData;
    if (nodes) delete []nodes;
    if (texinfos) delete []texinfos;
    if (faces) delete []faces;
    if (lightingData) delete []lightingData;
    if (clipnodes) delete []clipnodes;
    if (leafs) delete []leafs;
    if (marksurfaces) delete []marksurfaces;
    if (edges) delete []edges;
    if (surfedges) delete []surfedges;
    if (models) delete []models;
}

/*!
 * \brief
 * \param data
 * \return
 */
bool HlBspData::testBSP(const Data& data)
{
    hl::tBSPHeader header;
    
    if (!data.read(&header)) {
        std::cout << "Could not read the BSP header" << std::endl;
        return false;
    }

    if (header.signature != HL1_BSP_SIGNATURE) {
        std::cout << "Wrong BSP signature" << std::endl;
        return false;
    }

    if (header.lumps[HL1_BSP_PLANELUMP].size % sizeof(hl::tBSPPlane) != 0)
    {
        std::cout << "Plane lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_VERTEXLUMP].size % sizeof(hl::tBSPVertex) != 0)
    {
        std::cout << "Vertex lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_NODELUMP].size % sizeof(hl::tBSPNode) != 0)
    {
        std::cout << " Node lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_TEXINFOLUMP].size % sizeof(hl::tBSPTexInfo) != 0)
    {
        std::cout << "Texture info lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_FACELUMP].size % sizeof(hl::tBSPFace) != 0)
    {
        std::cout << "Face lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_CLIPNODELUMP].size % sizeof(hl::tBSPClipNode) != 0)
    {
        std::cout << "Clipnode lump has the wrond size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_LEAFLUMP].size % sizeof(hl::tBSPLeaf) != 0)
    {
        std::cout << "Leaf lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_EDGELUMP].size % sizeof(hl::tBSPEdge) != 0)
    {
        std::cout << "Edge lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[HL1_BSP_MODELLUMP].size % sizeof(hl::tBSPModel) != 0)
    {
        std::cout << "Model lump has the wrond size" << std::endl;
        return false;
    }

    return true;
}
