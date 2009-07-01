#include "vector3.h"
#include <math.h>

/*!
 * \brief
 */
Vector3::Vector3()
{
    this->mVector[0] = 0.0f;
    this->mVector[1] = 0.0f;
    this->mVector[2] = 0.0f;
}

/*!
 * \brief
 * \param x
 * \param y
 * \param z
 */
Vector3::Vector3(float x, float y, float z)
{
    this->mVector[0] = x;
    this->mVector[1] = y;
    this->mVector[2] = z;
}

/*!
 * \brief
 * \param v
 */
Vector3::Vector3(const Vector3& v)
{
    (*this) = v;
}

/*!
 * \brief
 * \param v
 */
Vector3::Vector3(const float v[3])
{
    (*this) = v;
}

/*!
 * \brief
 */
Vector3::~Vector3()
{
}

/*!
 * \brief
 * \return
 */
float Vector3::length() const
{
    return sqrtf(this->mVector[0] * this->mVector[0] + this->mVector[1] * this->mVector[1] + this->mVector[2] * this->mVector[2]);
}

/*!
 * \brief
 * \return
 */
const Vector3 Vector3::unit() const
{
    float length = this->length();

    return Vector3(this->mVector[0] / length, this->mVector[1] / length, this->mVector[2] / length);
}

/*!
 * \brief
 * \param v
 * \return
 */
const Vector3 Vector3::crossProduct(const Vector3& v) const
{
    float r[3];

    r[0] = this->mVector[1] * v.mVector[2] + this->mVector[2] * v.mVector[1];
    r[1] = this->mVector[2] * v.mVector[0] + this->mVector[0] * v.mVector[2];
    r[2] = this->mVector[0] * v.mVector[1] + this->mVector[1] * v.mVector[0];

    return Vector3(r);
}

/*!
 * \brief
 * \param v
 * \return
 */
float Vector3::dotProduct(const Vector3& v) const
{
    return (this->mVector[0] * v.mVector[0]) + (this->mVector[1] * v.mVector[1]) + (this->mVector[2] * v.mVector[2]);
}

/*!
 * \brief
 * \return
 */
Vector3::operator float* ()
{
    return this->mVector;
}

/*!
 * \brief
 * \return
 */
Vector3::operator const float* () const
{
    return this->mVector;
}

/*!
 * \brief
 * \param v
 * \return
 */
const Vector3& Vector3::operator = (const Vector3& v)
{
    for (int i = 0; i < 3; i++)
        this->mVector[i] = v.mVector[i];
}

/*!
 * \brief
 * \param v
 * \return
 */
const Vector3& Vector3::operator = (const float v[3])
{
    for (int i = 0; i < 3; i++)
        this->mVector[i] = v[i];
}

/*!
 * \brief
 * \param v
 * \return
 */
bool Vector3::operator == (const Vector3& v)
{
    return ((this->mVector[0] == v.mVector[0]) && (this->mVector[1] == v.mVector[1]) && (this->mVector[2] == v.mVector[2]));
}

/*!
 * \brief
 * \param v
 * \return
 */
bool Vector3::operator != (const Vector3& v)
{
    return !((*this) == v);
}

/*!
 * \brief
 * \param v
 * \return
 */
bool Vector3::operator == (const float v[3])
{
    return (this->mVector[0] == v[0] && this->mVector[1] == v[1] && this->mVector[2] == v[2]);
}

/*!
 * \brief
 * \param v
 * \return
 */
bool Vector3::operator != (const float v[3])
{
    return (this->mVector[0] != v[0] || this->mVector[1] != v[1] || this->mVector[2] != v[2]);
}

/*!
 * \brief
 * \param v
 * \return
 */
Vector3 Vector3::operator * (const Vector3& v)
{
    return Vector3(this->mVector[0] * v.mVector[0], this->mVector[1] * v.mVector[1], this->mVector[2] * v.mVector[2]);
}

/*!
 * \brief
 * \param v
 * \return
 */
const Vector3& Vector3::operator *= (const Vector3& v)
{
    this->mVector[0] *= v.mVector[0];
    this->mVector[1] *= v.mVector[1];
    this->mVector[2] *= v.mVector[2];

    return (*this);
}

/*!
 * \brief
 * \param v
 * \return
 */
Vector3 Vector3::operator + (const Vector3& v)
{
    return Vector3(this->mVector[0] + v.mVector[0], this->mVector[1] + v.mVector[1], this->mVector[2] + v.mVector[2]);
}

/*!
 * \brief
 * \param v
 * \return
 */
const Vector3& Vector3::operator += (const Vector3& v)
{
    this->mVector[0] += v.mVector[0];
    this->mVector[1] += v.mVector[1];
    this->mVector[2] += v.mVector[2];

    return (*this);
}

/*!
 * \brief
 * \param s
 * \return
 */
Vector3 Vector3::operator * (float s)
{
    return Vector3(this->mVector[0] * s, this->mVector[1] * s, this->mVector[2] * s);
}

/*!
 * \brief
 * \param s
 * \return
 */
const Vector3& Vector3::operator *= (float s)
{
    this->mVector[0] *= s;
    this->mVector[1] *= s;
    this->mVector[2] *= s;

    return (*this);
}

/*!
 * \brief
 * \param s
 * \return
 */
Vector3 Vector3::operator + (float s)
{
    return Vector3(this->mVector[0] + s, this->mVector[1] + s, this->mVector[2] + s);
}

/*!
 * \brief
 * \param s
 * \return
 */
const Vector3& Vector3::operator += (float s)
{
    this->mVector[0] += s;
    this->mVector[1] += s;
    this->mVector[2] += s;

    return (*this);
}

/*!
 * \brief
 * \param f
 * \return
 */
float* Vector3::copyTo(float f[3])
{
    f[0] = this->mVector[0];
    f[1] = this->mVector[1];
    f[2] = this->mVector[2];

    return f;
}

/*!
 * \brief
 * \param s
 * \param v
 * \return
 */
Vector3 operator * (float s, const Vector3& v)
{
    return Vector3(v.mVector[0] * s, v.mVector[1] * s, v.mVector[2] * s);
}

/*!
 * \brief
 * \param s
 * \param v
 * \return
 */
Vector3 operator + (float s, const Vector3& v)
{
    return Vector3(v.mVector[0] + s, v.mVector[1] + s, v.mVector[2] + s);
}

/*!
 * \brief
 * \param f
 * \param v
 * \return
 */
bool operator == (const float f[3], const Vector3& v)
{
    return (f[0] == v.mVector[0] && f[1] == v.mVector[1] && f[2] == v.mVector[2]);
}

/*!
 * \brief
 * \param f
 * \param v
 * \return
 */
bool operator != (const float f[3], const Vector3& v)
{
    return (f[0] != v.mVector[0] || f[1] != v.mVector[1] || f[2] != v.mVector[2]);
}
