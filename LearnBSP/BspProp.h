/* 
 * File:   BspProp.h
 * Author: wouter
 *
 * Created on December 25, 2009, 11:42 AM
 */

#ifndef _BSPPROP_H
#define	_BSPPROP_H

#include "fs/mesh/Mdl.h"
#include "BspObject.h"
#include "RenderMode.h"

class BspProp : public BspObject
{
public:
    BspProp(BspEntity* entity);
    virtual ~BspProp();

    virtual bool isType(const char* type) const;

    virtual void render(RenderOptions& options);
    virtual void onThink(ThinkArgs& args);
    virtual void onTouch(TouchArgs& args);

    virtual void preCache(fs::FileSystem& filesystem);

private:
    BspEntity* mEntity;
    Mdl* mMdlMesh;
    RenderMode mRenderMode;

};

#endif	/* _BSPPROP_H */

