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
#include "BspLeaf.h"
#include "BspModel.h"
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
 * \param point
 * \param set
 */
void BspNode::gatherVisibleModels(const float point[3], std::set<BspModel*>& set) const
{
    if (this->mLeaf != NULL)
    {
        this->mLeaf->gatherVisibleModels(set, true);
    }
    else
    {
        float distance = this->mSplit.distance(Vector3(point));

        if (distance >= 0)
            this->mFront->gatherVisibleModels(point, set);
        else
            this->mBack->gatherVisibleModels(point, set);
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
 * \param model
 */
void BspNode::addModel(BspModel* model)
{
    bool foundChild = false;
    if (this->mFront)
    {
        if (this->mFront->getBoundingBox().contains(model->getBoundingBox()))
        {
            foundChild = true;
            this->mFront->addModel(model);
        }
    }
    if (this->mBack)
    {
        if (this->mBack->getBoundingBox().contains(model->getBoundingBox()))
        {
            foundChild = true;
            this->mBack->addModel(model);
        }
    }
    if (foundChild == false)
    {
        this->mModels.push_back(model);
    }
}
