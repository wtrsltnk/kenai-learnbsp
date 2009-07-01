#include "math3d.h"

/*! 
 * \brief
 * \param first
 * \param second
 * \param out
 */
void multiplyMatrix(float first[16], float second[16], float out[16])
{
    out[0] = first[0]*second[0] + first[4]*second[1] + first[8]*second[2] + first[12]*second[3];
    out[1] = first[1]*second[0] + first[5]*second[1] + first[9]*second[2] + first[13]*second[3];
    out[2] = first[2]*second[0] + first[6]*second[1] + first[10]*second[2] + first[14]*second[3];
    out[3] = first[3]*second[0] + first[7]*second[1] + first[11]*second[2] + first[15]*second[3];

    out[4] = first[0]*second[4] + first[4]*second[5] + first[8]*second[6] + first[12]*second[7];
    out[5] = first[1]*second[4] + first[5]*second[5] + first[9]*second[6] + first[13]*second[7];
    out[6] = first[2]*second[4] + first[6]*second[5] + first[10]*second[6] + first[14]*second[7];
    out[7] = first[3]*second[4] + first[7]*second[5] + first[11]*second[6] + first[15]*second[7];

    out[8] = first[0]*second[8] + first[4]*second[9] + first[8]*second[10] + first[12]*second[11];
    out[9] = first[1]*second[8] + first[5]*second[9] + first[9]*second[10] + first[13]*second[11];
    out[10] = first[2]*second[8] + first[6]*second[9] + first[10]*second[10] + first[14]*second[11];
    out[11] = first[3]*second[8] + first[7]*second[9] + first[11]*second[10] + first[15]*second[11];

    out[12] = first[0]*second[12] + first[4]*second[13] + first[8]*second[14] + first[12]*second[15];
    out[13] = first[1]*second[12] + first[5]*second[13] + first[9]*second[14] + first[13]*second[15];
    out[14] = first[2]*second[12] + first[6]*second[13] + first[10]*second[14] + first[14]*second[15];
    out[15] = first[3]*second[12] + first[7]*second[13] + first[11]*second[14] + first[15]*second[15];
}

/*!
 * \brief
 * \param matrix
 * \param angle
 */
void rotateMatrixX(float matrix[16], float angle)
{
    for (int c = 0; c < 4; c++)
    {
        for(int r = 0; r < 4; r++)
        {
            matrix[c*4+r] = 0.0f;
        }
        matrix[c*4+c] = 1.0f;
    }

    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    matrix[5] =  cosAngle;
    matrix[9] = -sinAngle;
    matrix[6] =  sinAngle;
    matrix[10] =  cosAngle;
}

/*!
 * \brief
 * \param matrix
 * \param angle
 */
void rotateMatrixY(float matrix[16], float angle)
{
    for (int c = 0; c < 4; c++)
    {
        for(int r = 0; r < 4; r++)
        {
            matrix[c*4+r] = 0.0f;
        }
        matrix[c*4+c] = 1.0f;
    }

    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    matrix[0] =  cosAngle;
    matrix[8] =  sinAngle;
    matrix[2] = -sinAngle;
    matrix[10] =  cosAngle;
}

/*!
 * \brief
 * \param matrix
 * \param angle 
 */
void rotateMatrixZ(float matrix[16], float angle)
{
    for (int c = 0; c < 4; c++)
    {
        for(int r = 0; r < 4; r++)
        {
            matrix[c*4+r] = 0.0f;
        }
        matrix[c*4+c] = 1.0f;
    }

    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);

    matrix[0] =  cosAngle;
    matrix[4] = -sinAngle;
    matrix[1] =  sinAngle;
    matrix[5] =  cosAngle;
}

/*!
 * \brief
 * \param matrix
 * \return
 */
Vector3 forwardVector(float matrix[16])
{
    return Vector3(matrix[2], matrix[6], matrix[10]);
}

/*!
 * \brief
 * \param matrix
 * \return
 */
Vector3 leftVector(float matrix[16])
{
    return Vector3(matrix[0], matrix[4], matrix[8]);
}

/*!
 * \brief
 * \param matrix
 * \return
 */
Vector3 upVector(float matrix[16])
{
    return Vector3(matrix[1], matrix[5], matrix[9]);
}
