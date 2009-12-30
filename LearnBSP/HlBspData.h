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

#ifndef _HLBSPDATA_H
#define	_HLBSPDATA_H

#include "common/data.h"
#include "hltypes.h"
#include <stdlib.h>
#include "fs/Resource.h"

class HlBspData : public fs::Resource
{
public:
    HlBspData(const Data& data);
    virtual ~HlBspData();

    static bool testBSP(const Data& data);
    
    hl::tBSPHeader header;
    
//#define HL1_BSP_ENTITYLUMP 0
    int entitySize;
    unsigned char* entityData;

//#define HL1_BSP_PLANELUMP 1
    int planeCount;
    hl::tBSPPlane* planes;

//#define HL1_BSP_TEXTURELUMP 2
    int textureSize;
    unsigned char* textureData;

//#define HL1_BSP_VERTEXLUMP 3
    int vertexCount;
    hl::tBSPVertex* vertices;

//#define HL1_BSP_VISIBILITYLUMP 4
    int visibilitySize;
    unsigned char* visibilityData;

//#define HL1_BSP_NODELUMP 5
    int nodeCount;
    hl::tBSPNode* nodes;

//#define HL1_BSP_TEXINFOLUMP 6
    int texinfoCount;
    hl::tBSPTexInfo* texinfos;

//#define HL1_BSP_FACELUMP 7
    int faceCount;
    hl::tBSPFace* faces;

//#define HL1_BSP_LIGHTINGLUMP 8
    int lightingSize;
    unsigned char* lightingData;

//#define HL1_BSP_CLIPNODELUMP 9
    int clipnodeCount;
    hl::tBSPClipNode* clipnodes;

//#define HL1_BSP_LEAFLUMP 10
    int leafCount;
    hl::tBSPLeaf* leafs;

//#define HL1_BSP_MARKSURFACELUMP 11
    int marksurfaceCount;
    unsigned short* marksurfaces;

//#define HL1_BSP_EDGELUMP 12
    int edgeCount;
    hl::tBSPEdge* edges;

//#define HL1_BSP_SURFEDGELUMP 13
    int surfedgeCount;
    int* surfedges;

//#define HL1_BSP_MODELLUMP 14
    int modelCount;
    hl::tBSPModel* models;

private:
    /*!
     * \brief
     * \param array
     * \param lump
     * \param data
     */
    template <typename T>
    static int loadLump(T** array, const hl::tBSPLump& lump, const Data* data)
    {
        if (*array != NULL)
        {
            delete *array;
            *array = NULL;
        }

        if (data->dataSize < (lump.offset + lump.size))
            return 0;

        int count = lump.size / sizeof(T);
        if (count > 0)
        {
            *array = new T[count];
            if (*array == NULL)
                return 0;

            data->read(*array, count, lump.offset);
        }
        return count;
    }
};

#endif	/* _HLBSPDATA_H */

