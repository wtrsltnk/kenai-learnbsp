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

#include "boundingbox.h"

/*!
 * \brief
 */
BoundingBox::BoundingBox()
{
    this->mMins[0] = this->mMins[1] = this->mMins[2] = 99999.9f;
    this->mMaxs[0] = this->mMaxs[1] = this->mMaxs[2] = -99999.9f;
}

/*!
 * \brief
 * \param mins
 * \param maxs
 */
BoundingBox::BoundingBox(float mins[3], float maxs[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->mMins[i] = mins[i];
        this->mMaxs[i] = maxs[i];
    }
}

/*!
 * \brief
 * \param mins
 * \param maxs
 */
BoundingBox::BoundingBox(short mins[3], short maxs[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->mMins[i] = mins[i];
        this->mMaxs[i] = maxs[i];
    }
}

/*!
 * \brief
 * \param orig
 */
BoundingBox::BoundingBox(const BoundingBox& orig)
{
    for (int i = 0; i < 3; i++)
    {
        this->mMins[i] = orig.mMins[i];
        this->mMaxs[i] = orig.mMaxs[i];
    }
}

/*!
 * \brief
 */
BoundingBox::~BoundingBox()
{
}

/*!
 * \brief
 * \param point
 */
void BoundingBox::addPoint(float point[3])
{
    for (int i = 0; i < 3; i++)
    {
        if (point[i] < this->mMins[i])
            this->mMins[i] = point[i];
        if (point[i] > this->mMaxs[i])
            this->mMaxs[i] = point[i];
    }
}

/*!
 * \brief
 * \return
 */
const float* BoundingBox::getMins() const
{
    return this->mMins;
}

/*!
 * \brief
 * \return
 */
const float* BoundingBox::getMaxs() const
{
    return this->mMaxs;
}

