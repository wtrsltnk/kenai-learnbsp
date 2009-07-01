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

