/* 
 * File:   HlBspWorld.h
 * Author: wouter
 *
 * Created on December 18, 2009, 1:52 AM
 */

#ifndef _HLBSPWORLD_H
#define	_HLBSPWORLD_H

#include "BspWorld.h"

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

    bool parseEntityData(BspData& bsp, TextureLoader& textureLoader);
    bool parseTextures(BspData& bsp, TextureLoader& textureLoader);
    bool parseLeafs(BspData& bsp);
    bool parseFaces(BspData& bsp);
    bool parseModels(BspData& bsp);
    BspNode* createNode(const tBSPNode& node, BspData& bsp);
    
    void setWorldEntity(BspEntity* world);

    static void getFaceBounds(const tBSPFace& bspFace, const tBSPTexInfo& texinfo, BspData& bsp, float min[2], float max[2]);

};

#endif	/* _HLBSPWORLD_H */

