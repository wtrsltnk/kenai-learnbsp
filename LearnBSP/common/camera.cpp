#include "camera.h"
#include <GL/gl.h>
#include "math3d.h"

/*
 * \brief
 */
Camera::Camera()
{
    for (int i = 0; i < 3; i++)
        position[i] = rotation[i] = 0.0f;
    SetRotation(rotation);
}

/*
 * \brief
 */
Camera::~Camera()
{
}

/*
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
    ::glTranslatef(this->position[0], this->position[1], this->position[2]);
}

/*
 * \brief
 * \param position
 */
void Camera::SetPosition(float position[3])
{
    for (int i = 0; i < 3; i++)
        this->position[i] = position[i];
}

/*
 * \brief
 * \return
 */
const float* Camera::getPosition() const
{
    return this->position;
}

/*
 * \brief
 * \param rotation
 */
void Camera::SetRotation(float rotation[3])
{
    for (int i = 0; i < 3; i++)
        this->rotation[i] = rotation[i];

    float rx[16], ry[16], rz[16], tmp[16];

    rotateMatrixX(rx, rotation[0]);
    rotateMatrixY(ry, rotation[1]);
    rotateMatrixZ(rz, rotation[2]);

    multiplyMatrix(rx, ry, tmp);
    multiplyMatrix(tmp, rz, this->rotationMatrix);
}

/*
 * \brief
 * \return
 */
const float* Camera::getRotation() const
{
    return this->rotation;
}

/*
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

/*
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

/*
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

/*
 * \brief
 * \param forward
 * \param left
 * \param up
 */
void Camera::MoveGlobal(float forward, float left, float up)
{
    this->position[0] += forward;
    this->position[1] += left;
    this->position[2] += up;
}

/*
 * \brief
 * \param forward
 * \param left
 * \param up
 */
void Camera::MoveLocal(float forward, float left, float up)
{
    Vector3 vForward = forwardVector(rotationMatrix) * forward;
    Vector3 vLeft = leftVector(rotationMatrix) * left;
    Vector3 vUp = upVector(rotationMatrix) * up;
    Vector3 pos(position);

    pos += vForward + vLeft + vUp;
    pos.copyTo(position);
}
