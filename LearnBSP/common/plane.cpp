#include "plane.h"

/*!
 * \brief
 */
Plane::Plane()
{
    this->mDistance = 0;
}

/*!
 * \brief
 * \param plane
 */
Plane::Plane(const float plane[4])
{
    this->mNormal.x(plane[0]);
    this->mNormal.y(plane[1]);
    this->mNormal.z(plane[2]);
    this->mDistance = plane[3];
}

/*!
 * \brief
 * \param normal
 * \param distance
 */
Plane::Plane(const Vector3& normal, float distance)
{
    this->mNormal = normal;
    this->mDistance = distance;
}

/*!
 * \brief
 * \param orig
 */
Plane::Plane(const Plane& orig)
{
    this->mNormal = orig.mNormal;
    this->mDistance = orig.mDistance;
}

/*!
 * \brief
 */
Plane::~Plane()
{
}

/*!
 * \brief
 * \param vec
 * \return 
 */
float Plane::distance(const Vector3& vec) const
{
    return vec.dotProduct(this->mNormal) + this->mDistance;
}
