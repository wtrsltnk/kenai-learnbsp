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

#include "BspCollision.h"
#include "BspFace.h"
#include "BspNode.h"
#include "BspLeaf.h"
#include <iostream>

/*!
 * \brief
 * \param headnode
 */
BspCollision::BspCollision(BspNode* headnode, IndexArray<3>& vertices)
    : mHeadnode(headnode), mVertices(vertices), mLastIntersect(NULL)
{
}

/*!
 * \brief
 */
BspCollision::~BspCollision()
{
}

/*!
 * \brief
 * \param start
 * \param end
 * \return
 */
sCollisionData BspCollision::testCollision(Vector3& start, Vector3& end)
{
    sCollisionData result = { false, 9999.9f, NULL, 0, Vector3(), start };

    // Only go on when the there is line segment(camera is moved)
    Vector3 direction = (end - start);
    if (direction.length() == 0)
        return result;

	return testNode(this->mHeadnode, start, end);
}

/*!
 * \brief
 * \param node
 * \param start
 * \param end
 * \return
 */
sCollisionData BspCollision::testNode(BspNode* node, Vector3& start, Vector3& end)
{
    return testLeaf(node->getChild(start), start, end);
}

/*!
 * \brief
 * \param leaf
 * \param start
 * \param end
 * \return
 */
sCollisionData BspCollision::testLeaf(BspLeaf* leaf, Vector3& start, Vector3& end)
{
    sCollisionData result = { false, 9999.9f, NULL, 0, Vector3(), start };

	if (leaf != NULL)
	{
		for (std::set<BspFace*>::iterator face = leaf->getFaces().begin(); face != leaf->getFaces().end(); ++face)
		{
			sCollisionData faceResult = testFaceCollision(start, end, (*face));

			// Check if face collision found a hit and this hit is closer then the last found hit
			if (faceResult.hit && faceResult.t < result.t)
				result = faceResult;
		}
	}
    
    return result;
}

/*!
 * \brief
 * \param start
 * \param end
 * \param face
 * \return
 */
sCollisionData BspCollision::testFaceCollision(Vector3& start, Vector3& end, BspFace* face)
{
    sCollisionData result = { false, 9999.9f, NULL, 0, Vector3(), start };

    float startDistance = face->getPlane().distance(start);
    float endDistance = face->getPlane().distance(end);

    if ((!face->side && startDistance > 0 && endDistance < 0) || (startDistance < 0 && endDistance > 0))
    {
		float totalDistance = fabs(startDistance) + fabs(endDistance);
		Vector3 direction = (end - start).unit();
		result.t = (fabs(startDistance) / totalDistance) + EPSILON;
		result.hitpoint = start + (direction * result.t);
		result.hitObject = face;
		result.hit = point_in_poly(result.hitpoint, face);

		if (result.hit)
		{
			if (face->side)
			{
				float a = 2 * endDistance;
				Vector3 dir = face->getPlane().normal().unit();
				result.newPosition = end + (dir * a);
			}
			else
			{
				Vector3 tmp = face->getPlane().normal();
				tmp.inverseMe();
				result.newPosition = end + (tmp * (2 * endDistance));
			}
		}
		
		this->mLastIntersect = face;
    }

    return result;
}

/*!
 * \brief
 * \param hitpoint
 * \param face
 * \return
 */
bool BspCollision::point_in_poly(const Vector3& hitpoint, const BspFace* face)
{
    int i;
    Vector3 v[32];

    for (i = 0; i < face->getVertexCount(); i++)
    {
        int c = face->getFirstVertex() + i;
        Vector3 tmp = (Vector3)hitpoint - Vector3(this->mVertices[c]);
        v[i] = tmp.unit();
    }

    float total = 0.0f;

    for (i = 0; i < face->getVertexCount()-1; i++)
        total += (float) acos(DotProduct(v[i], v[i+1]));

    total += (float) acos(DotProduct(v[face->getVertexCount()-1], v[0]));

    if (fabs(total-6.28f)<0.01f)
        return true;

    return false;
}

