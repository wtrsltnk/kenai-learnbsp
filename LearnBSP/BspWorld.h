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

#include "common/camera.h"
#include "common/data.h"
#include "common/indexarray.h"
#include "common/texture.h"
#include "TextureLoader.h"
#include "BspNode.h"
#include "BspLeaf.h"
#include "BspFace.h"
#include "BspModel.h"
#include "BspData.h"
#include "BspEntity.h"
#include "types.h"
#include <vector>

/*!
 * \brief
 */
class BspWorld
{
public:
    BspWorld();
    virtual ~BspWorld();

    bool open(const Data& file, TextureLoader& textureLoader);
    void close();

    void render() const;
    void renderAllFaces() const;

    void setCamera(Camera* camera);

    const BspLeaf* getLeaf(const float position[3], int model = 0) const;
    const BspNode* getHeadNode(int model = 0) const;
    
private:
    Camera* mCamera;
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
    BspModel* mModels;
    /*! \brief */
    int mTextureCount;
    /*! \brief */
    Texture* mTextures;
    /*! \brief */
    std::vector<BspEntity*> mEntities;
    /*! \brief */
    IndexArray<3>* mVertexIndices;
    /*! \brief */
    IndexArray<2>* mLightmapUV;
    /*! \brief */
    IndexArray<2>* mTextureUV;

    bool parseEntities(BspData& bsp, TextureLoader& textureLoader);
    bool parseTextures(BspData& bsp, TextureLoader& textureLoader);
    bool parseNodes(BspData& bsp);
    bool parseLeafs(BspData& bsp);
    bool parseFaces(BspData& bsp);
    bool parseModels(BspData& bsp);
    
    void getFaceBounds(const tBSPFace& bspFace, const tBSPTexInfo& texinfo, BspData& bsp, float min[2], float max[2]);

};

#endif	/* _BSPWORLD_H */

