/*
 * Learn BSP is a sample source code to see how a Half-Life level file
 * can be used in your 3D application
 * Copyright (C) 2009  Wouter Saaltink

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BspLoader.h"
#include "HlBspWorld.h"
#include "Q3BspWorld.h"
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
	if (filename != NULL)
	{
		Data data;

		fs::Resource* resource = this->mFileSystem->openResource(filename);
		if (resource != NULL)
		{
			if (static_cast<HlBspData*>(resource) != NULL)
			{
				HlBspWorld* result = new HlBspWorld();
				if (result->open(resource, *this->mTextureLoader))
					return result;
				else
					delete result;
			}
			else if (static_cast<Q3BspData*>(resource) != NULL)
			{
				Q3BspWorld* result = new Q3BspWorld();
				if (result->open(resource, *this->mTextureLoader))
					return result;
				else
					delete result;
			}
		}
		if (this->mFileSystem->openFile(data, this->mFileSystem->findFile(filename)))
		{
			if (HlBspData::testBSP(data))
			{
				HlBspWorld* result = new HlBspWorld();
				if (result->open(resource, *this->mTextureLoader))
					return result;
				else
					delete result;
			}
			else if (Q3BspData::testBSP(data))
			{
				Q3BspWorld* result = new Q3BspWorld();
				if (result->open(resource, *this->mTextureLoader))
					return result;
				else
					delete result;
			}
		}
		std::cout << "Cannot load " << filename << std::endl;
	}
	return NULL;
}

