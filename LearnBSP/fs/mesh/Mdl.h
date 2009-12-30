/* 
 * File:   Mdl.h
 * Author: wouter
 *
 * Created on December 28, 2009, 3:17 PM
 */

#ifndef _MDL_H
#define	_MDL_H

#include "../../common/data.h"
#include "../../fs/FileSystem.h"
#include "../Resource.h"
#include "hlsdk/mdlviewer.h"

class Mdl : public fs::Resource
{
public:
    Mdl(Data& file, fs::FileSystem& filesystem);
    virtual ~Mdl();

    void initialize();
    void render();

private:
    fs::FileSystem& filesystem;
    Data file;
    StudioModel model;

};

#endif	/* _MDL_H */

