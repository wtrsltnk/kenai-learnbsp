/*
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

#ifndef _BSPCOLLISION_H
#define	_BSPCOLLISION_H

#include "BspNode.h"
#include "BspFace.h"
#include "common/math3d.h"
#include "common/indexarray.h"

/*!
 * \brief
 */
struct sCollisionData
{
    bool hit;           // True when a hit has been found, false otherwise
    float t;            // Startpoint = 0, Endpoint = 1, Hitpoint = t
    void* hitObject;    // The object that was hit
    int objectFlags;    // Flags describing the object that was hit (for exmaple if it is a solid or not)
    Vector3 hitpoint;   // Point where the line between Startpoint and Endpoint hit the object
    Vector3 newPosition;// New suggested position for the object
    
};

/*!
 * \brief
 */
class BspCollision
{
public:
    BspCollision(BspNode* headnode, IndexArray<3>& vertices);
    virtual ~BspCollision();

    sCollisionData testCollision(Vector3& start, Vector3& end);
    sCollisionData testNode(const BspNode* node, Vector3& start, Vector3& end);
    sCollisionData testLeaf(const BspLeaf* leaf, Vector3& start, Vector3& end);
    sCollisionData testFaceCollision(Vector3& start, Vector3& end, BspFace* face);
    bool planeIntersectLineSegment(const Plane& plane, const Vector3& pStart, const Vector3& pEnd, sCollisionData& intersection);
    bool point_in_poly(const Vector3& p, const BspFace* f);

    /*! \brief */
    BspFace* mLastIntersect;
private:
    /*! \brief */
    BspNode* mHeadnode;
    /*! \brief */
    IndexArray<3>& mVertices;

};

#endif	/* _BSPCOLLISION_H */

