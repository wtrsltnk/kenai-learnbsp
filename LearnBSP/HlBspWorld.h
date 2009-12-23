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

#ifndef _HLBSPWORLD_H
#define	_HLBSPWORLD_H

#include "BspWorld.h"
#include "HlBspData.h"

class HlBspWorld : public BspWorld
{
public:
    HlBspWorld();
    virtual ~HlBspWorld();

    const char* getTitle() const;
    const char* getSkyName() const;
    const char* getWad() const;
    int getWaveHeight() const;
    int getMaxRange() const;

protected:
    virtual bool onOpen(const Data& data, TextureLoader& textureLoader);
    
private:
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

    bool parseEntityData(HlBspData& bsp, TextureLoader& textureLoader);
    bool parseTextures(HlBspData& bsp, TextureLoader& textureLoader);
    bool parseLeafs(HlBspData& bsp);
    bool parseFaces(HlBspData& bsp);
    bool parseModels(HlBspData& bsp);
    BspNode* createNode(const hl::tBSPNode& node, const hl::tBSPModel& model, HlBspData& bsp);
    
    void setWorldEntity(BspEntity* world);

    static void getFaceBounds(const hl::tBSPFace& bspFace, const hl::tBSPTexInfo& texinfo, HlBspData& bsp, float min[2], float max[2]);

};

#endif	/* _HLBSPWORLD_H */

