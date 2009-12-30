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

#ifndef _BSPDATA_H
#define	_BSPDATA_H

#include "q3types.h"
#include "common/data.h"
#include <stdlib.h>
#include "fs/Resource.h"

class Q3BspData : public fs::Resource
{
public:
    Q3BspData(const Data& data);
    virtual ~Q3BspData();

    static bool testBSP(const Data& data);

    Q3::tBSPHeader header;
    
    /*! \brief */
    int entitySize;
    /*! \brief */
    unsigned char* entityData;

    /*! \brief */
    int textureCount;
    /*! \brief */
    Q3::tBSPTexture* textures;

    /*! \brief */
    int planeCount;
    /*! \brief */
    Q3::tBSPPlane* planes;

    /*! \brief */
    int nodeCount;
    /*! \brief */
    Q3::tBSPNode* nodes;

    /*! \brief */
    int leafCount;
    /*! \brief */
    Q3::tBSPLeaf* leafs;

    /*! \brief */
    int leafFaceCount;
    /*! \brief */
    Q3::tBSPLeafFace* leafFaces;

    /*! \brief */
    int leafBrushCount;
    /*! \brief */
    Q3::tBSPLeafBrush* leafBrushes;

    /*! \brief */
    int modelCount;
    /*! \brief */
    Q3::tBSPModel* models;

    /*! \brief */
    int brushCount;
    /*! \brief */
    Q3::tBSPBrush* brushes;

    /*! \brief */
    int brushSideCount;
    /*! \brief */
    Q3::tBSPBrushSide* brushSides;

    /*! \brief */
    int vertexCount;
    /*! \brief */
    Q3::tBSPVertex* vertices;

    /*! \brief */
    int meshVertCount;
    /*! \brief */
    Q3::tBSPMeshVert* meshVerts;

    /*! \brief */
    int effectCount;
    /*! \brief */
    Q3::tBSPEffect* effects;

    /*! \brief */
    int faceCount;
    /*! \brief */
    Q3::tBSPFace* faces;

    /*! \brief */
    int lightmapCount;
    /*! \brief */
    Q3::tBSPLightMap* lightmaps;

    /*! \brief */
    int lightVolumeCount;
    /*! \brief */
    Q3::tBSPLightVolume* lightVolumes;

    /*! \brief */
    int visDataSize;
    /*! \brief */
    Q3::ubyte* visData;

private:
    /*!
     * \brief
     * \param array
     * \param lump
     * \param data
     */
    template <typename T>
    static int loadLump(T** array, const Q3::tBSPLump& lump, const Data* data)
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

#endif	/* _BSPDATA_H */

