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
#include "math3d.h"

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
BoundingBox::BoundingBox(const float mins[3], const float maxs[3])
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
BoundingBox::BoundingBox(const short mins[3], const short maxs[3])
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
 * \param point
 */
void BoundingBox::offset(float point[3])
{
    for (int i = 0; i < 3; i++)
    {
        this->mMins[i] += point[i];
        this->mMaxs[i] += point[i];
    }
}

/*!
 * \brief
 * \param x
 * \param y
 * \param z
 */
void BoundingBox::offset(float x, float y, float z)
{
    this->mMins[0] += x;
    this->mMins[1] += y;
    this->mMins[2] += z;
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

/*!
 * \brief
 * \param plane
 * \return
 */
int BoundingBox::intersect(const Plane& plane) const
{
    Vector3 diagMin, diagMax;

    if(plane.normal().x() >= 0)
    {
        diagMin.x(this->mMins[0]);
        diagMax.x(this->mMaxs[0]);
    }
    else
    {
        diagMin.x(this->mMaxs[0]);
        diagMax.x(this->mMins[0]);
    }

    if(plane.normal().y() >= 0)
    {
        diagMin.y(this->mMins[1]);
        diagMax.y(this->mMaxs[1]);
    }
    else
    {
        diagMin.y(this->mMaxs[1]);
        diagMax.y(this->mMins[1]);
    }

    if(plane.normal().z() >= 0)
    {
        diagMin.z(this->mMins[2]);
        diagMax.z(this->mMaxs[2]);
    }
    else
    {
        diagMin.z(this->mMaxs[2]);
        diagMax.z(this->mMins[2]);
    }

    float test = DotProduct(plane.normal(), diagMin) + plane.distance();
    if(test > 0.0f)
        return 1;

    test = DotProduct(plane.normal(), diagMax) + plane.distance();
    if(test > 0.0f)
        return -1;

    return 0;
}

/*!
 * \brief
 * \param bb
 * \return
 */
bool BoundingBox::intersect(const BoundingBox& bb) const
{
    if (mMins[0] > bb.mMaxs[0] || mMaxs[0] < bb.mMins[0]) return false;
    if (mMins[1] > bb.mMaxs[1] || mMaxs[1] < bb.mMins[1]) return false;
    if (mMins[2] > bb.mMaxs[2] || mMaxs[2] < bb.mMins[2]) return false;

    return true;
}

/*!
 * \brief
 * \param bb
 * \return
 */
bool BoundingBox::contains(const BoundingBox& bb) const
{
    return
        bb.mMins[0] >= this->mMins[0] && bb.mMaxs[0] <= this->mMaxs[0] &&
        bb.mMins[1] >= this->mMins[1] && bb.mMaxs[1] <= this->mMaxs[1] &&
        bb.mMins[2] >= this->mMins[2] && bb.mMaxs[2] <= this->mMaxs[2];
}
