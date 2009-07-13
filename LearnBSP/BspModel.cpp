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
    : mHeadNode(NULL), mFxAmount(1.0f), mFxMode(4)
{
    this->mFxColor[0] = this->mFxColor[1] = this->mFxColor[2] = 1.0f;
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
void BspModel::render() const
{
    setupShader();
    for (std::vector<BspFace*>::const_iterator face = this->mFaces.begin(); face != this->mFaces.end(); ++face)
    {
        (*face)->render();
    }
}

/*!
 * \brief
 * \param position
 */
void BspModel::render(const float position[3]) const
{
    setupShader();
    this->mHeadNode->render(position);
}

/*!
 * \brief
 */
void BspModel::setupShader() const
{
    switch (mFxMode)
    {
        case 1:	// Color blending
        {
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_ALPHA_TEST);
            glDisable(GL_BLEND);
            glColor3f(mFxColor[0], mFxColor[1], mFxColor[2]);
            break;
        }
        case 3:	// Glow blending
        case 5:	// Additive blending
        {
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_ALPHA_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glColor4f(1.0f, 1.0f, 1.0f, mFxAmount);
            break;
        }
        case 4:	// Solid blending
        {
            glEnable(GL_TEXTURE_2D);

            // Enable alpha testing to make sure transparent textures are drawn correct
            glEnable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GEQUAL, 0.8f);

            // Default blending acoording to the alpha value of texture
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 1.0f, 1.0f, mFxAmount);
            break;
        }
        case 0:	// Normal blending
        case 2:	// Texture blending
        {
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_ALPHA_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glColor4f(1.0f, 1.0f, 1.0f, mFxAmount);
            break;
        }
        default:
        {
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_ALPHA_TEST);
            glDisable(GL_BLEND);
            break;
        }
    }
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

    for (int k = 0; k < this->mEntity->getKeyCount(); k++)
    {
        const char* key = this->mEntity->getKey(k);
        const char* value = this->mEntity->getValue(k);
        
        if (strcasecmp(key, "renderamt") == 0)
        {
            int renderamt;
            sscanf(value, "%d", &renderamt);
            this->mFxAmount = (float)renderamt / 255.0f;
        }
        else if (strcasecmp(key, "rendermode") == 0)
        {
            sscanf(value, "%d", &this->mFxMode);
        }
        else if (strcasecmp(key, "rendercolor") == 0)
        {
            int r, g, b;
            sscanf(value, "%d %d %d", &r, &g, &b);
            if (r || g || b)
            {
                this->mFxColor[0] = (float)r / 255.0f;
                this->mFxColor[1] = (float)g / 255.0f;
                this->mFxColor[2] = (float)b / 255.0f;
            }
        }
    }
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
 * \param model
 */
void BspModel::addModel(BspModel* model)
{
    this->mHeadNode->addModel(model);
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
