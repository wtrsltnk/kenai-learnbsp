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
#include "common/renderoperations.h"
#include <iostream>
#include <string.h>

/*!
 * \brief
 */
BspModel::BspModel()
    : mHeadNode(NULL)
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
void BspModel::update(double time)
{
}

/*!
 * \brief
 */
void BspModel::render() const
{
    for (std::vector<BspFace*>::const_iterator face = this->mFaces.begin(); face != this->mFaces.end(); ++face)
    {
        (*face)->render();
    }
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
 * \param face
 */
void BspModel::addFace(BspFace* face)
{
    this->mFaces.push_back(face);
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
