/*
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

#include "BspData.h"
#include <iostream>
#include <string.h>

BspData::BspData(const DataBlock& data)
    : entitySize(0), entityData(NULL), textureCount(0), textures(NULL), planeCount(0), planes(NULL),
        nodeCount(0), nodes(NULL), leafCount(0), leafs(NULL), leafFaceCount(0), leafFaces(NULL),
        leafBrushCount(0), leafBrushes(NULL), modelCount(0), models(NULL), brushCount(0), brushes(NULL),
        brushSideCount(0), brushSides(NULL), vertexCount(0), vertices(NULL), meshVertCount(0), meshVerts(NULL),
        effectCount(0), effects(NULL), faceCount(0), faces(NULL), lightmapCount(0), lightmaps(NULL),
        lightVolumeCount(0), lightVolumes(NULL), visDataSize(0), visData(NULL)
{
    if (!data.read(&this->header)) {
        std::cout << "Could not read the BSP header" << std::endl;
        return;
    }

    if (this->header.signature != Q3_BSP_SIGNATURE) {
        std::cout << "Wrong BSP signature" << std::endl;
        return;
    }

    if (this->header.version != Q3_BSP_VERSION) {
        std::cout << "Wrong BSP version" << std::endl;
        return;
    }

    this->entitySize = loadLump(&this->entityData, header.lumps[Q3_BSP_ENTITIES], &data);
    this->textureCount = loadLump(&this->textures, header.lumps[Q3_BSP_TEXTURES], &data);
    this->planeCount = loadLump(&this->planes, header.lumps[Q3_BSP_PLANES], &data);
    this->nodeCount = loadLump(&this->nodes, header.lumps[Q3_BSP_NODES], &data);
    this->leafCount = loadLump(&this->leafs, header.lumps[Q3_BSP_LEAFS], &data);
    this->leafFaceCount = loadLump(&this->leafFaces, header.lumps[Q3_BSP_LEAFFACES], &data);
    this->leafBrushCount = loadLump(&this->leafBrushes, header.lumps[Q3_BSP_LEAFBRUSHES], &data);
    this->modelCount = loadLump(&this->models, header.lumps[Q3_BSP_MODELS], &data);
    this->brushCount = loadLump(&this->brushes, header.lumps[Q3_BSP_BRUSHES], &data);
    this->brushSideCount = loadLump(&this->brushSides, header.lumps[Q3_BSP_BRUSHSIDES], &data);
    this->vertexCount = loadLump(&this->vertices, header.lumps[Q3_BSP_VERTICES], &data);
    this->meshVertCount = loadLump(&this->meshVerts, header.lumps[Q3_BSP_MESHVERTS], &data);
    this->effectCount = loadLump(&this->effects, header.lumps[Q3_BSP_EFFECTS], &data);
    this->faceCount = loadLump(&this->faces, header.lumps[Q3_BSP_FACES], &data);
    this->lightmapCount = loadLump(&this->lightmaps, header.lumps[Q3_BSP_LIGHTMAPS], &data);
    this->lightVolumeCount = loadLump(&this->lightVolumes, header.lumps[Q3_BSP_LIGHTVOLUMES], &data);
    this->visDataSize = loadLump(&this->visData, header.lumps[Q3_BSP_VISDATA], &data);
}

BspData::~BspData()
{
    if (entityData) delete []entityData;
    if (textures) delete []textures;
    if (planes) delete []planes;
    if (nodes) delete []nodes;
    if (leafs) delete []leafs;
    if (leafFaces) delete []leafFaces;
    if (leafBrushes) delete []leafBrushes;
    if (models) delete []models;
    if (brushes) delete []brushes;
    if (brushSides) delete []brushSides;
    if (vertices) delete []vertices;
    if (meshVerts) delete []meshVerts;
    if (effects) delete []effects;
    if (faces) delete []faces;
    if (lightmaps) delete []lightmaps;
    if (lightVolumes) delete []lightVolumes;
    if (visData) delete []visData;
}

bool BspData::testBSP(const DataBlock& data)
{
    Q3::tBSPHeader header;
    
    if (!data.read(&header)) {
        std::cout << "Could not read the BSP header" << std::endl;
        return false;
    }

    if (header.signature != Q3_BSP_SIGNATURE) {
        std::cout << "Wrong BSP signature" << std::endl;
        return false;
    }

    if (header.version != Q3_BSP_VERSION) {
        std::cout << "Wrong BSP version" << std::endl;
        return false;
    }

    if (header.lumps[Q3_BSP_TEXTURES].size % sizeof(Q3::tBSPTexture) != 0)
    {
        std::cout << "Texture lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_PLANES].size % sizeof(Q3::tBSPPlane) != 0)
    {
        std::cout << "Plane lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_NODES].size % sizeof(Q3::tBSPNode) != 0)
    {
        std::cout << "Node lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_LEAFS].size % sizeof(Q3::tBSPLeaf) != 0)
    {
        std::cout << "Leaf lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_LEAFFACES].size % sizeof(Q3::tBSPLeafFace) != 0)
    {
        std::cout << "Leaf face lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_LEAFBRUSHES].size % sizeof(Q3::tBSPLeafBrush) != 0)
    {
        std::cout << "Leaf brush lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_MODELS].size % sizeof(Q3::tBSPModel) != 0)
    {
        std::cout << "Model lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_BRUSHES].size % sizeof(Q3::tBSPBrush) != 0)
    {
        std::cout << "Brush lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_BRUSHSIDES].size % sizeof(Q3::tBSPBrushSide) != 0)
    {
        std::cout << "Brush side lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_VERTICES].size % sizeof(Q3::tBSPVertex) != 0)
    {
        std::cout << "Vertex lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_MESHVERTS].size % sizeof(Q3::tBSPMeshVert) != 0)
    {
        std::cout << "Mesh verts lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_EFFECTS].size % sizeof(Q3::tBSPEffect) != 0)
    {
        std::cout << "Effect lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_FACES].size % sizeof(Q3::tBSPFace) != 0)
    {
        std::cout << "Face lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_LIGHTMAPS].size % sizeof(Q3::tBSPLightMap) != 0)
    {
        std::cout << "Lightmap lump has the wrong size" << std::endl;
        return false;
    }
    if (header.lumps[Q3_BSP_LIGHTVOLUMES].size % sizeof(Q3::tBSPLightVolume) != 0)
    {
        std::cout << "Light volume lump has the wrong size" << std::endl;
        return false;
    }
    return true;
}

