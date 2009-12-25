/* 
 * File:   RenderMode.h
 * Author: wouter
 *
 * Created on December 25, 2009, 1:22 AM
 */

#ifndef _RENDERMODE_H
#define	_RENDERMODE_H

class RenderMode
{
public:
    RenderMode();
    virtual ~RenderMode();

    void setupFx() const;

    float mFxAmount;
    int mFxMode;
    float mFxColor[3];
    float mOrigin[3];

};

#endif	/* _RENDERMODE_H */

