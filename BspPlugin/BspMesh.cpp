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

#include "BspMesh.h"
#include "../LearnBSP/opengl.h"
#include <string.h>

/*!
 * \brief
 */
BspMesh::BspMesh()
    : mIsSolid(false), mFxAmount(1.0f), mFxMode(4)
{
    this->mFxColor[0] = this->mFxColor[1] = this->mFxColor[2] = 1.0f;
}

/*!
 * \brief
 */
BspMesh::~BspMesh()
{
}

/*!
 * \brief
 */
void BspMesh::setupShader() const
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
        {
            glEnable(GL_TEXTURE_2D);
            glDisable(GL_ALPHA_TEST);
            glDisable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glColor4f(1.0f, 1.0f, 1.0f, mFxAmount);
            break;
        }
        case 2:	// Texture blending
        {
            glEnable(GL_TEXTURE_2D);

            // Enable alpha testing to make sure transparent textures are drawn correct
            glDisable(GL_ALPHA_TEST);
            glAlphaFunc(GL_GEQUAL, 0.8f);

            // Default blending acoording to the alpha value of texture
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
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            break;
        }
    }
}

/*!
 * \brief
 * \param solid
 */
void BspMesh::setSolid(bool solid)
{
    this->mIsSolid = solid;
}

/*!
 * \brief
 * \return
 */
bool BspMesh::isSolid() const
{
    return this->mIsSolid;
}

/*!
 * \brief
 * \param mode
 */
void BspMesh::setFxMode(int mode)
{
    this->mFxMode = mode;
}

/*!
 * \brief
 * \return
 */
int BspMesh::getFxMode() const
{
    return this->mFxMode;
}

/*!
 * \brief
 * \param color
 */
void BspMesh::setFxColor(float color[3])
{
    for (int i = 0; i < 3; i++)
        this->mFxColor[i] = color[i];
}

/*!
 * \brief
 * \return
 */
const float* BspMesh::getFxColor() const
{
    return this->mFxColor;
}

/*!
 * \brief
 * \param amount
 */
void BspMesh::setFxAmount(float amount)
{
    this->mFxAmount = amount;
}

/*!
 * \brief
 * \return
 */
float BspMesh::getFxAmount() const
{
    return this->mFxAmount;
}

/*!
 * \brief
 * \return
 */
void BspMesh::getBoundingBox(float mins[3], float maxs[3]) const
{
    for (int i = 0; i < 3; i++)
    {
        mins[i] = this->mMins[i];
        maxs[i] = this->mMaxs[i];
    }
}

/*!
 * \brief
 * \param entityKeys
 */
void BspMesh::setEntity(const std::map<std::string, std::string>& entityKeys)
{
    for (std::map<std::string, std::string>::const_iterator itr = entityKeys.begin(); itr != entityKeys.end(); ++itr)
    {
        const char* key = (*itr).first.c_str();
        const char* value = (*itr).second.c_str();

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