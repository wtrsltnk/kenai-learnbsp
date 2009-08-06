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


#include "BspNode.h"
#include "BspLeaf.h"
#include "BspModel.h"
#include "Collision.h"
#include "common/plane.h"
#include <BspObject.h>
#include <iostream>

/*!
 * \brief
 */
BspNode::BspNode()
    : mParent(NULL), mFront(NULL), mBack(NULL), mLeaf(NULL)
{
}

/*!
 * \brief
 * \param leaf
 */
BspNode::BspNode(BspLeaf* leaf)
    : mFront(NULL), mBack(NULL), mLeaf(leaf), index(-leaf->index)
{
}

/*!
 * \brief
 */
BspNode::~BspNode()
{
}

/*!
 * \brief
 */
void BspNode::render() const
{
    if (this->mLeaf != NULL)
    {
        this->mLeaf->render(false);
    }
    else
    {
        this->mFront->render();
        this->mBack->render();
    }
}

/*!
 * \brief
 * \param position
 */
void BspNode::render(const float point[3]) const
{
    if (this->mLeaf != NULL)
    {
        this->mLeaf->render();
    }
    else
    {
        float distance = this->mSplit.distance(Vector3(point));

        if (distance >= 0)
            this->mFront->render(point);
        else
            this->mBack->render(point);
    }
}

/*!
 * \brief
 * \param start
 * \param end
 * \return
 */
Collision BspNode::getCollision(const Vector3& start, const Vector3& end)
{
    if (this->mLeaf != NULL)
    {
        return this->mLeaf->getCollision(start, end);
    }
    else
    {
        float dStart = this->mSplit.distance(start);
        float dEnd = this->mSplit.distance(end);

        if ((dStart > 0) && (dEnd > 0))
        {
            return this->mFront->getCollision(start, end);
        }
        else if ((dStart < 0) && (dEnd < 0))
        {
            return this->mBack->getCollision(start, end);
        }
        else
        {
            Vector3 intersection = Collision::getIntersection(this->mSplit, start, end);

            if (dStart > 0)
                return this->mFront->getCollision(start, intersection);
            
            return this->mBack->getCollision(start, intersection);
        }
    }
}

/*!
 * \brief
 * \param normal
 * \param distance
 */
void BspNode::setPlane(float normal[3], float distance)
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
const BspNode* BspNode::getChild(const float point[3]) const
{
    if (this->mLeaf == NULL)
    {
        float distance = this->mSplit.distance(Vector3(point));

        if (distance >= 0)
            return this->mFront;
        else
            return this->mBack;
    }

    return NULL;
}

/*!
 * \brief
 * \param point
 * \return
 */
const BspLeaf* BspNode::getLeaf(const float position[3]) const
{
    const BspNode* child = this->getChild(position);

    if (child == NULL)
        return this->mLeaf;

    return child->getLeaf(position);
}

/*!
 * \brief
 * \return
 */
const BspLeaf* BspNode::getLeaf() const
{
    return this->mLeaf;
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
}
