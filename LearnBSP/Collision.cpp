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

#include "Collision.h"
#include <stdlib.h>

/*!
 * \brief
 */
Collision::Collision()
    : mCollidingFace(NULL), mCollidingLeaf(NULL), mIsColliding(false)
{
}

/*!
 * \brief
 * \param leaf
 * \\param face
 * \param point
 */
Collision::Collision(BspLeaf* leaf, BspFace* face, const Vector3& point)
    : mCollidingLeaf(leaf), mCollidingFace(face), mCollisionPoint(point), mIsColliding(true)
{
}

/*!
 * \brief
 */
Collision::~Collision()
{
}

/*!
 * \brief
 * \param node
 * \param face
 * \param point
 */
void Collision::setCollision(BspLeaf* leaf, BspFace* face, const Vector3& point)
{
    this->mCollidingLeaf = leaf;
    this->mCollidingFace = face;
    this->mCollisionPoint = point;

    this->mIsColliding = true;
}

/*!
 * \brief
 * \return 
 */
BspLeaf* Collision::getCollidingLeaf() const
{
    return this->mCollidingLeaf;
}

/*!
 * \brief
 * \return
 */
BspFace* Collision::getCollidingFace() const
{
    return this->mCollidingFace;
}

/*!
 * \brief
 * \return
 */
const Vector3& Collision::getCollisionPoint() const
{
    return this->mCollisionPoint;
}

/*!
 * \brief
 * \return
 */
bool Collision::isColliding() const
{
    return this->mIsColliding;
}

/*!
 * \brief
 * \param plane
 * \param start
 * \param end
 * \return
 */
Vector3 Collision::getIntersection(const Plane& plane, const Vector3& start, const Vector3& end)
{
    Vector3 ray = (Vector3)end - (Vector3)start;
    float splitRay = plane.normal().dotProduct(ray);
    float t = 1.0f;

    if (splitRay != 0)
        t = - ( plane.normal().dotProduct(start) + plane.distance() ) / splitRay;
    
    return (Vector3)start + (ray * t);
}

/*!
 * \brief
 * \param plane
 * \param point
 * \return
 */
ePointClassification Collision::classifyPoint(const Plane& plane, const Vector3& point)
{
    float d = plane.distance(point);

    if (d > 0)
        return ClassFront;

    if (d < 0)
        return ClassBack;
    
    return ClassCoincide;
}