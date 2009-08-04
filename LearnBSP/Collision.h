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

#ifndef _COLLISION_H
#define	_COLLISION_H

#include "common/math3d.h"

class BspLeaf;
class BspFace;

enum ePointClassification
{
    ClassBack = -1,
    ClassCoincide,
    ClassFront,
};

/*!
 * \brief
 */
class Collision
{
public:
    Collision();
    Collision(BspLeaf* leaf, BspFace* face, const Vector3& point);
    virtual ~Collision();

    void setCollision(BspLeaf* leaf, BspFace* face, const Vector3& point);
    
    BspLeaf* getCollidingLeaf() const;
    BspFace* getCollidingFace() const;
    const Vector3& getCollisionPoint() const;
    bool isColliding() const;

    static Vector3 getIntersection(const Plane& plane, const Vector3& start, const Vector3& end);
    static ePointClassification classifyPoint(const Plane& plane, const Vector3& point);

private:
    /*! \brief */
    BspLeaf* mCollidingLeaf;
    /*! \brief */
    BspFace* mCollidingFace;
    /*! \brief */
    Vector3 mCollisionPoint;
    /*! \brief */
    bool mIsColliding;

};

#endif	/* _COLLISION_H */

