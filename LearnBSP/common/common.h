/* 
 * File:   common.h
 * Author: wouter
 *
 * Created on December 24, 2009, 12:40 PM
 */

#ifndef _COMMON_H
#define	_COMMON_H

#include "boundingbox.h"

class Common
{
public:
    virtual ~Common() { }

    /// String functions
    static const char* getFilename(const char* fullname);
    static const char* getExtention(const char* fullname);

    /// Render functions
    static void renderBoundingBox(const BoundingBox& bb);
    void renderGrid(float gridsize, float gridcount);
    void renderCrosshair(float size);
    
};

#endif	/* _COMMON_H */

