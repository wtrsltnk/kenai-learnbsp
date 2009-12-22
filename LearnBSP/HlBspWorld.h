/* 
 * File:   HlBspWorld.h
 * Author: wouter
 *
 * Created on December 18, 2009, 1:52 AM
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
    BspNode* createNode(const hl::tBSPNode& node, HlBspData& bsp);
    
    void setWorldEntity(BspEntity* world);

    static void getFaceBounds(const hl::tBSPFace& bspFace, const hl::tBSPTexInfo& texinfo, HlBspData& bsp, float min[2], float max[2]);

};

#endif	/* _HLBSPWORLD_H */

