/* 
 * File:   BspLoader.h
 * Author: wouter
 *
 * Created on December 22, 2009, 7:11 PM
 */

#ifndef _BSPLOADER_H
#define	_BSPLOADER_H

#include "BspWorld.h"

class BspLoader
{
public:
    BspLoader(fs::FileSystem* filesystem);
    virtual ~BspLoader();

    BspWorld* loadWorld(const char* filename);

private:
    TextureLoader* mTextureLoader;
    fs::FileSystem* mFileSystem;

};

#endif	/* _BSPLOADER_H */

