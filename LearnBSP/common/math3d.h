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

#ifndef _MATH3D_H
#define	_MATH3D_H

#include <math.h>
#include "vector3.h"
#include "plane.h"

/*!
 * \brief 
 */
#define DotProduct(x,y) ((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])

void multiplyMatrix(float first[16], float second[16], float out[16]);
void rotateMatrixX(float matrix[16], float angle);
void rotateMatrixY(float matrix[16], float angle);
void rotateMatrixZ(float matrix[16], float angle);

Vector3 forwardVector(float matrix[16]);
Vector3 leftVector(float matrix[16]);
Vector3 upVector(float matrix[16]);

#endif	/* _MATH3D_H */

