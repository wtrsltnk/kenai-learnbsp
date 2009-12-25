/* 
 * File:   BspProp.h
 * Author: wouter
 *
 * Created on December 25, 2009, 11:42 AM
 */

#ifndef _BSPPROP_H
#define	_BSPPROP_H

#include "BspObject.h"

class BspProp : public BspObject
{
public:
    BspProp(float origin[3], const char* mesh);
    virtual ~BspProp();

    virtual bool isType(const char* type) const;

    virtual void render(RenderOptions& options) const;
    virtual const BspMesh* getMesh() const;
    virtual void onThink(ThinkArgs& args);
    virtual void onTouch(TouchArgs& args);

    virtual void preCache();

private:
    char mMeshName[256];

};

#endif	/* _BSPPROP_H */

