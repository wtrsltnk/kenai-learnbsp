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

#include "BspNode.h"
#include <iostream>

/*!
 * \brief
 */
BspNode::BspNode()
    : mFront(NULL), mBack(NULL), mLeaf(NULL)
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
 * \param normal
 * \param distance
 */
void BspNode::setPlane(float normal[3], float distance)
{
    this->mSplit = Plane(normal, distance);
}

/*!
 * \brief
 * \param front
 * \param back
 */
void BspNode::setChildren(BspNode* front, BspNode* back)
{
    this->mFront = front;
    this->mBack = back;
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
 * \return
 */
const BspLeaf* BspNode::getLeaf() const
{
    return this->mLeaf;
}

void BspNode::render() const
{
    if (this->mLeaf != NULL)
    {
        this->mLeaf->render(false);
    }
    else
    {
        if (this->mFront != NULL) this->mFront->render();
        if (this->mBack != NULL) this->mBack->render();
    }
}
