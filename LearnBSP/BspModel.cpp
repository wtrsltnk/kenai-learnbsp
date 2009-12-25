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

#include "BspModel.h"
#include "BspFace.h"
#include "BspNode.h"
#include "BspEntity.h"
#include "BspLeaf.h"
#include "RenderMode.h"
#include <stdio.h>
#include <iostream>

/*!
 * \brief
 */
BspModel::BspModel()
    : mHeadNode(NULL), mEntity(NULL)
{
}

/*!
 * \brief
 */
BspModel::~BspModel()
{
    if (this->mHeadNode != NULL)
        delete this->mHeadNode;
}

/*!
 * \brief
 * \param time
 */
void BspModel::update(RenderOptions& options)
{
}

/*!
 * \brief
 */
void BspModel::render(RenderOptions& options) const
{
	glPushMatrix();
	this->mRenderMode.setupFx();
	
	const BspLeaf* leaf = this->mHeadNode->getChild(options.getCamera()->getPosition());
	if (leaf != NULL)
	{
		leaf->render();
	}
	else
	{
		for (std::vector<BspFace*>::const_iterator face = this->mFaces.begin(); face != this->mFaces.end(); ++face)
		{
			(*face)->render();
		}
	}
	glPopMatrix();
}

/*!
 * \brief
 */
void BspModel::renderAllFaces() const
{
	glPushMatrix();
	this->mRenderMode.setupFx();
	for (std::vector<BspFace*>::const_iterator face = this->mFaces.begin(); face != this->mFaces.end(); ++face)
	{
		(*face)->render();
	}
	glPopMatrix();
}

/*!
 * \brief
 * \return
 */
const BspLeaf* BspModel::getLeaf(const float position[3]) const
{
    return this->mHeadNode->getChild(position);
}

/*!
 * \brief
 * \param node
 */
void BspModel::setHeadNode(BspNode* node)
{
    this->mHeadNode = node;
}

/*!
 * \brief
 * \return
 */
BspNode* BspModel::getHeadNode()
{
    return this->mHeadNode;
}

/*!
 * \brief
 * \return
 */
void BspModel::setEntity(BspEntity* entity)
{
    this->mEntity = entity;

	if (this->mEntity != NULL)
	{
		const Map& values = this->mEntity->getValues();
		for (Map::const_iterator value = values.begin(); value != values.end(); ++value)
		{
			if ((*value).first == "origin")
			{
				int x, y, z;
				if (sscanf((*value).second.c_str(), "%d %d %d", &x, &y, &z) != false)
				{
					this->mRenderMode.mOrigin[0] = x;
					this->mRenderMode.mOrigin[1] = y;
					this->mRenderMode.mOrigin[2] = z;
				}
			}
			else if ((*value).first == "rendermode")
			{
				int mode = 0;
				if (sscanf((*value).second.c_str(), "%d", &mode) != false)
					this->mRenderMode.mFxMode = mode;
				std::cout << (*value).second << " " << this->mRenderMode.mFxMode << std::endl;
			}
			else if ((*value).first == "rendercolor")
			{
				int r, g, b;
				if (sscanf((*value).second.c_str(), "%d %d %d", &r, &g, &b) != false)
				{
					this->mRenderMode.mFxColor[0] = (float)r / 255.0f;
					this->mRenderMode.mFxColor[1] = (float)g / 255.0f;
					this->mRenderMode.mFxColor[2] = (float)b / 255.0f;
				}
			}
			else if ((*value).first == "renderamt")
			{
				int renderamt;
				if (sscanf((*value).second.c_str(), "%d", &renderamt) != false)
					this->mRenderMode.mFxAmount = (float)renderamt / 255.0f;
				std::cout << (*value).second << " " << this->mRenderMode.mFxAmount << std::endl;
			}
		}
	}
}

/*!
 * \brief
 * \return
 */
BspEntity* BspModel::getEntity()
{
    return this->mEntity;
}

/*!
 * \brief
 * \param face
 */
void BspModel::addFace(BspFace* face)
{
    this->mFaces.push_back(face);
}

/*!
 * \brief
 * \param face
 */
void BspModel::addObject(BspObject* object)
{
	this->mHeadNode->addObject(object);
}

/*!
 * \brief
 * \param bb
 */
void BspModel::setBoundingBox(const BoundingBox& bb)
{
    this->mBB = bb;
}

/*!
 * \brief
 * \return
 */
const BoundingBox& BspModel::getBoundingBox() const
{
    return this->mBB;
}
