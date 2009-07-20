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

#ifndef _PLANE_H
#define	_PLANE_H

#include "vector3.h"

/*!
 * \brief
 */
class Plane
{
public:
    Plane();
    Plane(const float plane[4]);
    Plane(const Vector3& normal, float distance);
    Plane(const Plane& orig);
    virtual ~Plane();

    float distance(const Vector3& vec) const;
    const Vector3& normal() const;
    float distance() const;

private:
    /*! \brief */
    Vector3 mNormal;
    /*! \brief */
    float mDistance;

};

#endif	/* _PLANE_H */

