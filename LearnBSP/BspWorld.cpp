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

#include "BspWorld.h"
#include "BspProp.h"
#include "common/common.h"
#include <iostream>
#include <vector>

/*!
 * \brief
 */
BspWorld::BspWorld(Progress* progress)
    : mProgress(progress), mLeafCount(0), mLeafs(NULL), mFaceCount(0), mFaces(NULL), mModelCount(0), mGeometries(NULL),
        mTextureCount(0), mTextures(NULL), mWorldEntity(NULL),
        mVertexIndices(NULL), mTextureUV(NULL), mLightmapUV(NULL)
{
}

/*!
 * \brief
 */
BspWorld::~BspWorld() 
{
    close();
}

/*!
 * \brief
 * \param data
 * \return 
 */
bool BspWorld::open(fs::Resource* resource, TextureLoader& textureLoader)
{
	return this->onOpen(resource, textureLoader);
}

/*!
 * \brief
 * \return
 */
bool BspWorld::setupEntities(fs::FileSystem& filesystem)
{
	this->mGeometries[0].setEntity(this->mWorldEntity);
    for (std::vector<BspEntity*>::iterator itr = this->mEntities.begin(); itr != this->mEntities.end(); ++itr)
    {
        BspEntity* entity = *itr;
		const char* model = entity->getValue("model");
		const char* classname = entity->getValue("classname");
		
		if (model != NULL)
		{
			int index = 0;
			if (sscanf(model, "*%d", &index) != false)
			{
				/// Index == 0 is not possible, thats the worldspawn!
				if (index > 0 && index < this->mModelCount)
					this->mGeometries[index].setEntity(entity);
			}
		}
		if (Common::stringCompare(classname, "cycler_sprite") == 0)
		{
			const char* origin = entity->getValue("origin");
			float position[3];
			if (sscanf(origin, "%f %f %f", &position[0], &position[1], &position[2]))
			{
				BspProp* prop = new BspProp(entity);
				this->mObjects.push_back(prop);
				prop->preCache(filesystem);
			}
		}
    }
	if (this->mCameraPositions.begin() != this->mEntities.end())
	{
		BspEntity* entity = this->mCameraPositions[0];

		float position[3];
		const char* origin = entity->getValue("origin");
		if (sscanf(origin, "%f %f %f", &position[0], &position[1], &position[2]))
			this->mCamera->SetPosition(position);
	}
    return true;
}

/*!
 * \brief
 * \param camera
 */
void BspWorld::setCamera(Camera* camera)
{
    this->mCamera = camera;
}

/*!
 * \brief
 */
void BspWorld::render()
{
	RenderOptions options(this->mCamera, 1.0f);

	this->mGeometries[0].render(options);
	for (int m = 1; m < this->mModelCount; m++)
	{
		this->mGeometries[m].renderAllFaces();
	}
	for (std::vector<BspObject*>::const_iterator itr = this->mObjects.begin(); itr != this->mObjects.end(); ++itr)
	{
		(*itr)->render(options);
	}
}

/*!
 * \brief
 */
void BspWorld::renderAllFaces()
{
    for (int f = 1; f < this->mFaceCount; f++)
    {
        this->mFaces[f].render();
    }
}

/*!
 * \brief
 */
void BspWorld::shoot()
{
	for (int m = 0; m < this->mModelCount; m++)
	{
		 const BspLeaf* leaf = this->mGeometries[m].getHeadNode()->getChild(this->mCamera->getPosition());
		 if (leaf != NULL)
		 {
			 std::cout << "Entity: " << this->mGeometries[m].getEntity()->getClassName() << "Found leaf" << std::endl;
		 }
	}
}

/*!
 * \brief
 */
void BspWorld::close()
{
	if (this->mTextures != NULL)
        delete []this->mTextures;
    this->mTextures = NULL;
    this->mTextureCount = 0;

    if (this->mLeafs != NULL)
        delete []this->mLeafs;
    this->mLeafs = NULL;
    this->mLeafCount = 0;

    if (this->mFaces != NULL)
        delete []this->mFaces;
    this->mFaces = NULL;
    this->mFaceCount = 0;

    if (this->mGeometries != NULL)
        delete []this->mGeometries;
    this->mGeometries = NULL;
    this->mModelCount = 0;

    if (this->mVertexIndices != NULL)
        delete this->mVertexIndices;
    this->mVertexIndices = NULL;

    if (this->mTextureUV != NULL)
        delete this->mTextureUV;
    this->mTextureUV = NULL;

    if (this->mLightmapUV != NULL)
        delete this->mLightmapUV;
    this->mLightmapUV = NULL;

    while (!this->mEntities.empty())
    {
        BspEntity* entity = this->mEntities.back();
        this->mEntities.pop_back();
        delete entity;
    }

//    while (!this->mObjects.empty())
//    {
//        BspObject* object = this->mObjects.back();
//        this->mObjects.pop_back();
//        delete object;
//    }
}
