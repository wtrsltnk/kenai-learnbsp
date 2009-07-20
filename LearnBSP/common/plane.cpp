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

#include "plane.h"

/*!
 * \brief
 */
Plane::Plane()
{
    this->mDistance = 0;
}

/*!
 * \brief
 * \param plane
 */
Plane::Plane(const float plane[4])
{
    this->mNormal.x(plane[0]);
    this->mNormal.y(plane[1]);
    this->mNormal.z(plane[2]);
    this->mDistance = plane[3];
}

/*!
 * \brief
 * \param normal
 * \param distance
 */
Plane::Plane(const Vector3& normal, float distance)
{
    this->mNormal = normal;
    this->mDistance = distance;
}

/*!
 * \brief
 * \param orig
 */
Plane::Plane(const Plane& orig)
{
    this->mNormal = orig.mNormal;
    this->mDistance = orig.mDistance;
}

/*!
 * \brief
 */
Plane::~Plane()
{
}

/*!
 * \brief
 * \param vec
 * \return 
 */
float Plane::distance(const Vector3& vec) const
{
    return vec.dotProduct(this->mNormal) - this->mDistance;
}

/*!
 * \brief
 * \return
 */
const Vector3& Plane::normal() const
{
    return this->mNormal;
}

/*!
 * \brief
 * \return
 */
float Plane::distance() const
{
    return this->mDistance;
}
