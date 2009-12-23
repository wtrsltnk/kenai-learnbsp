/* 
 * File:   RenderOptions.h
 * Author: wouter
 *
 * Created on December 23, 2009, 5:36 PM
 */

#ifndef _RENDEROPTIONS_H
#define	_RENDEROPTIONS_H

#include "common/camera.h"

class RenderOptions
{
public:
    RenderOptions(Camera* camera, double time);
    virtual ~RenderOptions();
    
    Camera* getCamera();
    double getTime();

private:
    Camera* mCamera;
    double mTime;

};

#endif	/* _RENDEROPTIONS_H */

