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

#include "BspGeometry.h"
#include "BspFace.h"
#include "BspNode.h"
#include "BspEntity.h"
#include "BspLeaf.h"
#include "RenderMode.h"
#include "common/common.h"
#include <iostream>
#include <stdio.h>

/*!
 * \brief
 */
BspGeometry::BspGeometry()
    : mHeadNode(NULL), mEntity(NULL)
{
}

/*!
 * \brief
 */
BspGeometry::~BspGeometry()
{
    if (this->mHeadNode != NULL)
        delete this->mHeadNode;
}

/*!
 * \brief
 * \param time
 */
void BspGeometry::update(RenderOptions& options)
{
}

/*!
 * \brief
 */
void BspGeometry::render(RenderOptions& options)
{
	glPushMatrix();
	this->mRenderMode.setupFx();
	
	BspLeaf* leaf = this->mHeadNode->getChild(options.getCamera()->getPosition());
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
void BspGeometry::renderAllFaces()
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
BspLeaf* BspGeometry::getLeaf(const float position[3])
{
    return this->mHeadNode->getChild(position);
}

/*!
 * \brief
 * \param node
 */
void BspGeometry::setHeadNode(BspNode* node)
{
    this->mHeadNode = node;
}

/*!
 * \brief
 * \return
 */
BspNode* BspGeometry::getHeadNode()
{
    return this->mHeadNode;
}

/*!
 * \brief
 * \return
 */
void BspGeometry::setEntity(BspEntity* entity)
{
    this->mEntity = entity;
	RenderMode::fromEntity(entity, this->mRenderMode);
}

/*!
 * \brief
 * \return
 */
BspEntity* BspGeometry::getEntity()
{
    return this->mEntity;
}

/*!
 * \brief
 * \param face
 */
void BspGeometry::addFace(BspFace* face)
{
    this->mFaces.push_back(face);
}

/*!
 * \brief
 * \param face
 */
void BspGeometry::addObject(BspObject* object)
{
	this->mHeadNode->addObject(object);
}

/*!
 * \brief
 * \param bb
 */
void BspGeometry::setBoundingBox(const BoundingBox& bb)
{
    this->mBB = bb;
}

/*!
 * \brief
 * \return
 */
const BoundingBox& BspGeometry::getBoundingBox() const
{
    return this->mBB;
}
