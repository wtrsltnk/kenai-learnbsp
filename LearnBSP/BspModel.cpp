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

#include <GL/gl.h>

#include "BspModel.h"
#include "common/renderoperations.h"

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
}

/*!
 * \brief
 */
void BspModel::render(bool renderHeadNode) const
{
    for (std::vector<BspFace*>::const_iterator face = this->mFaces.begin(); face != this->mFaces.end(); ++face)
    {
        (*face)->render();
    }
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    if (renderHeadNode)
    {
        glColor3f(1.0f, 0, 0);
        if (this->mHeadNode != NULL) RenderOperations::renderBoundingBox(this->mHeadNode->getBoundingBox());
    }
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glColor3f(1.0f, 1.0f, 1.0f);
}

/*!
 * \brief
 * \return
 */
const BspLeaf* BspModel::getLeaf(const float position[3]) const
{
    const BspNode* node = this->getHeadNode();
    const BspNode* child = node->getChild(position);

    while (child != NULL)
    {
        node = child;
        child = node->getChild(position);
    }
    return node->getLeaf();
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
const BspNode* BspModel::getHeadNode() const
{
    return this->mHeadNode;
}

/*!
 * \brief
 * \param entity
 */
void BspModel::setEntity(BspEntity* entity)
{
    this->mEntity = entity;
}

/*!
 * \brief
 * \return
 */
const BspEntity* BspModel::getEntity() const
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
 * \param origin
 */
void BspModel::setOrigin(Vector3 origin)
{
    this->mOrigin = origin;
}

/*!
 * \brief
 * \return
 */
const Vector3& BspModel::getOrigin() const
{
    return this->mOrigin;
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
