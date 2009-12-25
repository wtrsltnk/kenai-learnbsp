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

#ifndef _BOUNDINGBOX_H
#define	_BOUNDINGBOX_H

#include "plane.h"

/*!
 * \brief
 */
class BoundingBox
{
public:
    BoundingBox();
    BoundingBox(const float mins[3], const float maxs[3]);
    BoundingBox(const short mins[3], const short maxs[3]);
    BoundingBox(const BoundingBox& orig);
    virtual ~BoundingBox();

    void addPoint(float point[3]);
    void offset(float point[3]);
    void offset(float x, float y, float z);

    const float* getMins() const;
    const float* getMaxs() const;

    int intersect(const Plane& plane) const;
    bool intersect(const BoundingBox& bb) const;
    bool contains(const BoundingBox& bb) const;
    bool contains(const float* point) const;
    
private:
    /*! \brief */
    float mMins[3];
    /*! \brief */
    float mMaxs[3];

};

#endif	/* _BOUNDINGBOX_H */

