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

private:
    /*! \brief */
    Vector3 mNormal;
    /*! \brief */
    float mDistance;

};

#endif	/* _PLANE_H */

