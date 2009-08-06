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

#include "camera.h"
#include <opengl.h>
#include "math3d.h"

/*!
 * \brief
 */
Camera::Camera()
    : mHasChanged(true)
{
    for (int i = 0; i < 3; i++)
        position[i] = rotation[i] = 0.0f;
    SetRotation(rotation);
}

/*!
 * \brief
 */
Camera::~Camera()
{
}

/*!
 * \brief
 */
void Camera::Update()
{
    // Reset the view matrix to identity(no transformations)
    ::glLoadIdentity();

    // First rotate the sceen around the origin. This makes this camera rotate around it's position (FPS camera)
    ::glMultMatrixf(this->rotationMatrix);

    // Then move the camera to the correct position in space
    // By tranlating in the opposite direction, we move the camera instead of moving the world
    ::glTranslatef(-this->position[0], -this->position[1], -this->position[2]);
}

/*!
 * \brief
 * \param position
 */
void Camera::SetPosition(float position[3])
{
    for (int i = 0; i < 3; i++)
        this->position[i] = position[i];
}

/*!
 * \brief
 * \return
 */
const float* Camera::getPosition() const
{
    return this->position;
}

/*!
 * \brief
 * \return
 */
const float* Camera::getPreviousPosition() const
{
    return this->previousPosition;
}

/*!
 * \brief
 * \param rotation
 */
void Camera::SetRotation(float rotation[3])
{
    if (rotation[0] == 0 && rotation[1] == 0 && rotation[2] == 0)
        return;
    
    for (int i = 0; i < 3; i++)
        this->rotation[i] = rotation[i];

    float rx[16], ry[16], rz[16], tmp[16];

    rotateMatrixX(rx, rotation[0]);
    rotateMatrixY(ry, rotation[1]);
    rotateMatrixZ(rz, rotation[2]);

    multiplyMatrix(rx, ry, tmp);
    multiplyMatrix(tmp, rz, this->rotationMatrix);
    this->mHasChanged = true;
}

/*!
 * \brief
 * \return
 */
const float* Camera::getRotation() const
{
    return this->rotation;
}

/*!
 * \brief
 * \return
 */
const float* Camera::getForwardVector() const
{
    static float forward[3] = { 0 };

    forward[0] = this->rotationMatrix[2];
    forward[1] = this->rotationMatrix[6];
    forward[2] = this->rotationMatrix[10];

    return forward;
}

/*!
 * \brief
 * \param up
 */
const float* Camera::getLeftVector() const
{
    static float left[3] = { 0 };

    left[0] = this->rotationMatrix[1];
    left[1] = this->rotationMatrix[5];
    left[2] = this->rotationMatrix[9];

    return left;
}

/*!
 * \brief
 * \param up
 */
const float* Camera::getUpVector() const
{
    static float up[3] = { 0 };

    up[0] = this->rotationMatrix[0];
    up[1] = this->rotationMatrix[4];
    up[2] = this->rotationMatrix[8];

    return up;
}

/*!
 * \brief
 * \param forward
 * \param left
 * \param up
 */
void Camera::MoveGlobal(float forward, float left, float up)
{
    if (forward == 0 && left == 0 && up == 0)
        return;

    this->position[0] += forward;
    this->position[1] += left;
    this->position[2] += up;
    this->mHasChanged = true;
}

/*!
 * \brief
 * \param forward
 * \param left
 * \param up
 */
void Camera::MoveLocal(float forward, float left, float up)
{
    if (forward == 0 && left == 0 && up == 0)
        return;

    Vector3 vForward = forwardVector(rotationMatrix) * forward;
    Vector3 vLeft = leftVector(rotationMatrix) * left;
    Vector3 vUp = upVector(rotationMatrix) * up;
    Vector3 pos(position);

    pos += vForward + vLeft + vUp;
    pos.copyTo(position);
    this->mHasChanged = true;
}

/*!
 * \brief
 */
void Camera::resetChanged()
{
    this->mHasChanged = false;
    for (int i = 0; i < 3; i++)
        this->previousPosition[i] = this->position[i];
}

/*!
 * \brief
 * \return
 */
bool Camera::hasChanged() const
{
    return this->mHasChanged;
}
