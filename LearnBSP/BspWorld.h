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
#include <BspObject.h>
#include <vector>
#include <set>

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

    void render();
    void renderAllFaces() const;

    void setCamera(Camera* camera);

    const char* getTitle() const;
    const char* getSkyName() const;
    const char* getWad() const;
    int getWaveHeight() const;
    int getMaxRange() const;

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
    std::vector<BspObject*> mObjects;

    /*! \brief */
    BspNode* mHeadNode;
    /*! \brief */
    BspEntity* mWorldEntity;

    /*! \brief */
    char* mTitle;
    /*! \brief */
    char* mSkyName;
    /*! \brief */
    char* mWad;
    /*! \brief */
    int mWaveHeight;
    /*! \brief */
    int mMaxRange;
    
    /*! \brief */
    std::set<BspModel*> mRenderModels;
    /*! \brief */
    IndexArray<3>* mVertexIndices;
    /*! \brief */
    IndexArray<2>* mLightmapUV;
    /*! \brief */
    IndexArray<2>* mTextureUV;

    bool parseEntityData(BspData& bsp, TextureLoader& textureLoader);
    bool parseTextures(BspData& bsp, TextureLoader& textureLoader);
    bool parseNodes(BspData& bsp);
    bool parseLeafs(BspData& bsp);
    bool parseFaces(BspData& bsp);
    bool parseModels(BspData& bsp);
    bool setupEntities();
    
    void setWorldEntity(BspEntity* world);
    void getFaceBounds(const tBSPFace& bspFace, const tBSPTexInfo& texinfo, BspData& bsp, float min[2], float max[2]);

};

#endif	/* _BSPWORLD_H */

