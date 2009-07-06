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

#ifndef _BSPWORLD_H
#define	_BSPWORLD_H

#include "common/data.h"
#include "common/indexarray.h"
#include "BspNode.h"
#include "BspLeaf.h"
#include "BspFace.h"
#include "types.h"

/*!
 * \brief
 */
class BspWorld
{
public:
    BspWorld();
    virtual ~BspWorld();

    bool open(const Data& file);
    void close();

    void renderAllFaces() const;

    const BspLeaf* getLeaf(const float position[3], int model = 0) const;
    const BspNode* getHeadNode(int model = 0) const;
    
private:
    /*! \brief */
    int mNodeCount;
    /*! \brief */
    BspNode* mNodes;
    /*! \brief */
    int mLeafCount;
    /*! \brief */
    BspLeaf* mLeafs;
    /*! \brief */
    int mFaceCount;
    /*! \brief */
    BspFace* mFaces;
    /*! \brief */
    int mModelCount;
    /*! \brief */
    tBSPModel* mModels;
    /*! \brief */
    IndexArray<3>* mVertexIndices;
    /*! \brief */
    IndexArray<2>* mLightmapUV;
    /*! \brief */
    IndexArray<2>* mTextureUV;

    bool testFile(const Data& file, tBSPHeader& header);
    
    /*! 
     * \brief
     * \param array
     * \param lump
     * \param data
     */
    template <typename T>
    static int loadLump(T** array, const tBSPLump& lump, const Data* data)
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

#endif	/* _BSPWORLD_H */

