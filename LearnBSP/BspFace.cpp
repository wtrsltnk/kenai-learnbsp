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
#include "common/math3d.h"
#include <string.h>

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
    if (this->mLightmap != NULL)
        delete this->mLightmap;
}

/*!
 * \brief
 */
void BspFace::render()
{
    if (this->mTexture != NULL)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->mTexture->glIndex);
    }
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
 * \param texture
 */
void BspFace::setTexture(Texture* texture)
{
    this->mTexture = texture;
}

/*!
 * \brief
 * \return
 */
const Texture* BspFace::getTexture() const
{
    return this->mTexture;
}

/*!
 * \brief
 * \param bspFace
 * \param min
 * \param max
 * \param lightData
 * \param brughtness
 * \return
 */
const Texture* BspFace::setLightmap(const tBSPFace& bspFace, float min[2], float max[2], const unsigned char* lightData, float brightness)
{
    if (this->mLightmap != NULL)
        delete this->mLightmap;
    
    this->mLightmap = new Texture;

    // compute lightmap size
    int size[2];
    for (int c = 0; c < 2; c++)
    {
        float tmin = floorf(min[c] / 16.0f);
        float tmax = ceilf(max[c] / 16.0f);

        size[c] = (int) (tmax - tmin);
    }

    this->mLightmap->width = size[0] + 1;
    this->mLightmap->height = size[1] + 1;
    this->mLightmap->bpp = 3;
    this->mLightmap->repeat = false;

    int dataSize = this->mLightmap->width * this->mLightmap->height * this->mLightmap->bpp;  // RGB buffer size

    this->mLightmap->data = new unsigned char[dataSize];

    memcpy(this->mLightmap->data, lightData + bspFace.lightOffset, dataSize);

    // scale lightmap value...
    for (int i = 0; i < dataSize; i++)
    {
        float f = powf((this->mLightmap->data[i] + 1) / 256.0f, brightness);
        int inf = int(f * 255.0f + 0.5f);

        // clamp between 0 and 255
        if (inf < 0) inf = 0;
        if (inf > 255) inf = 255;

        this->mLightmap->data[i] = inf;
    }
    // Really important! make sure the unpack alignment is set to 1
    glActiveTexture(GL_TEXTURE1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    this->mLightmap->upload();
    
    return this->mLightmap;
}

