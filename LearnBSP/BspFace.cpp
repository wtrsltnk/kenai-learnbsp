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

#include "BspFace.h"
#include "common/texture.h"

/*!
 * \brief
 */
BspFace::BspFace()
    : mLightmap(NULL)
{
}

/*!
 * \brief
 */
BspFace::~BspFace()
{
}

/*!
 * \brief
 */
void BspFace::render()
{
    if (this->mLightmap != NULL)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->mLightmap->glIndex);
    }
    glDrawArrays(this->mFaceType, this->mFirstVertex, this->mVertexCount);
}

/*!
 * \brief
 * \param normal
 * \param distance
 */
void BspFace::setPlane(float normal[3], float distance)
{
    this->mPlane = Plane(normal, distance);
}

/*!
 * \brief
 * \param first
 * \param count
 */
void BspFace::setVertices(int first, int count)
{
    this->mFirstVertex = first;
    this->mVertexCount = count;
    
    switch (count)
    {
        case 3: this->mFaceType = GL_TRIANGLES; break;
        case 4: this->mFaceType = GL_QUADS; break;
        default: this->mFaceType = GL_POLYGON; break;
    }
}

/*!
 * \brief
 * \param flags 
 */
void BspFace::setFlags(int flags)
{
    this->mFaceFlags = flags;
}

/*!
 * \brief
 * \param lightmap
 */
void BspFace::setLightmap(Texture* lightmap)
{
    this->mLightmap = lightmap;
}

