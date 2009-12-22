/* 
 * File:   BspLoader.cpp
 * Author: wouter
 * 
 * Created on December 22, 2009, 7:11 PM
 */

#include "BspLoader.h"
#include "HlBspData.h"
#include "HlBspWorld.h"
#include <iostream>

BspLoader::BspLoader(fs::FileSystem* filesystem)
	: mFileSystem(filesystem), mTextureLoader(new TextureLoader(filesystem))
{
}

BspLoader::~BspLoader()
{
	delete this->mTextureLoader;
}

BspWorld* BspLoader::loadWorld(const char* filename)
{
	Data data;
	
    if (this->mFileSystem->openFile(data, this->mFileSystem->findFile(filename)))
	{
		if (HlBspData::testBSP(data))
		{
			HlBspWorld* result = new HlBspWorld();
			if (result->open(data, *this->mTextureLoader))
				return result;
			else
				delete result;
		}
	}
	std::cout << "Cannot load " << filename << std::endl;
	return NULL;
}

