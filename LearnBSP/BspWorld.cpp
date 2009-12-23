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
#include "common/tokenizer.h"
#include <iostream>
#include <string.h>

/*!
 * \brief
 */
BspWorld::BspWorld()
    : mLeafCount(0), mLeafs(NULL), mFaceCount(0), mFaces(NULL), mModelCount(0), mModels(NULL),
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
bool BspWorld::open(const Data& data, TextureLoader& textureLoader)
{
	return this->onOpen(data, textureLoader);
}

/*!
 * \brief
 * \return
 */
bool BspWorld::setupEntities()
{
    for (std::vector<BspEntity*>::const_iterator itr = this->mEntities.begin(); itr != this->mEntities.end(); ++itr)
    {
        const BspEntity* entity = *itr;
        const char* classname = entity->getClassName();
        BspObject* object = NULL;//PluginManager::Instance()->getEntityInstance(classname, entity->getValues());
        if (object != NULL)
        {
            this->mObjects.push_back(object);
        }
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

	for (int m = 0; m < 1; m++)
	{
		this->mModels[m].render(options);
	}
}

/*!
 * \brief
 */
void BspWorld::renderAllFaces() const
{
    for (int f = 1; f < this->mFaceCount; f++)
    {
        this->mFaces[f].render();
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

    if (this->mModels != NULL)
        delete []this->mModels;
    this->mModels = NULL;
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

    while (!this->mObjects.empty())
    {
        BspObject* object = this->mObjects.back();
        this->mObjects.pop_back();
        delete object;
    }
}
