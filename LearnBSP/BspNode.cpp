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

#include "common/vector3.h"
#include "common/plane.h"
#include "BspNode.h"
#include "BspLeaf.h"
#include "BspModel.h"
#include "BspObject.h"
#include <iostream>

/*!
 * \brief
 */
BspNode::BspNode()
    : mParent(NULL), mFront(NULL), mBack(NULL)
{
}

/*!
 * \brief
 */
BspNode::~BspNode()
{
	// Only remove the BspNode objects, the BspLeaf objects get removed another way
    if (this->mFront != NULL && static_cast <BspLeaf*> (this->mFront) == NULL)
        delete this->mFront;

    if (this->mBack != NULL && static_cast <BspLeaf*> (this->mBack) == NULL)
        delete this->mBack;
}

/*!
 * \brief
 */
void BspNode::render() const
{
	this->mFront->render();
	this->mBack->render();
}

/*!
 * \brief
 * \param position
 */
void BspNode::render(const float point[3]) const
{
	float distance = this->mSplit.distance(Vector3(point));

	if (distance < 0)
		this->mBack->render(point);
	else
		this->mFront->render(point);
}

/*!
 * \brief
 * \param objects
 * \param position
 */
void BspNode::gatherVisibleObjects(std::set<BspObject*>& objects, const float point[3]) const
{
	float distance = this->mSplit.distance(Vector3(point));

	if (distance < 0)
		this->mBack->gatherVisibleObjects(objects, point);
	else
		this->mFront->gatherVisibleObjects(objects, point);
}

/*!
 * \brief
 * \param normal
 * \param distance
 */
void BspNode::setPlane(const float normal[3], float distance)
{
    this->mSplit = Plane(normal, distance);
}

/*!
 * \brief
 * \return
 */
const Plane& BspNode::getPlane() const
{
    return this->mSplit;
}

/*!
 * \brief
 * \param front
 * \param back
 */
void BspNode::setChildren(BspNode* front, BspNode* back)
{
    this->mFront = front;
    if (this->mFront != NULL)
        this->mFront->mParent = this;
    this->mBack = back;
    if (this->mBack != NULL)
        this->mBack->mParent = this;
}

/*!
 * \brief
 * \return
 */
const BspNode* BspNode::getFront() const
{
    return this->mFront;
}

/*!
 * \brief
 * \return
 */
const BspNode* BspNode::getBack() const
{
    return this->mBack;
}

/*!
 * \brief
 * \return
 */
const BspNode* BspNode::getParent() const
{
    return this->mParent;
}

/*!
 * \brief
 * \param point
 * \return
 */
const BspLeaf* BspNode::getChild(const float point[3]) const
{
	float distance = this->mSplit.distance(Vector3(point));

	if (distance < 0)
		return this->mBack->getChild(point);

	return this->mFront->getChild(point);
}

/*!
 * \brief
 * \param bb
 */
void BspNode::setBoundingBox(const BoundingBox& bb)
{
    this->mBB = bb;
}

/*!
 * \brief
 * \return
 */
const BoundingBox& BspNode::getBoundingBox() const
{
    return this->mBB;
}

/*!
 * \brief
 * \param object
 */
void BspNode::addObject(BspObject* object)
{
	float distance = this->mSplit.distance(Vector3(object->getOrigin()));

	if (distance < 0)
		this->mBack->addObject(object);
	else
		this->mFront->addObject(object);
}
