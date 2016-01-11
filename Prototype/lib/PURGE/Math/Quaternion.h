// NOTE THAT THIS FILE IS BASED ON MATERIAL FROM:

// Magic Software, Inc.
// http://www.geometrictools.com/
// Copyright (c) 2000, All Rights Reserved
//
// Source code from Magic Software is supplied under the terms of a license
// agreement and may not be copied or disclosed except in accordance with the
// terms of that agreement.  The various license agreements may be found at
// the Magic Software web site.  This file is subject to the license
//
// FREE SOURCE CODE
// http://www.geometrictools.com/License/WildMagic3License.pdf

#ifndef PURGE_QUATERNION_H
#define PURGE_QUATERNION_H

#include "Angle.h"
#include "Vector3.h"
#include <string.h>

namespace PURGE
{

	class Quaternion
	{

		public:

			static const Quaternion ZERO;
			static const Quaternion IDENTITY;

			static const Real defaultTolerance;

			Quaternion();
			Quaternion(Real w, Real x, Real y, Real z);
			Quaternion(const Quaternion& q);
			Quaternion(const Angle& angle, const Vector3& axis);

			Real w() const;
			Real x() const;
			Real y() const;
			Real z() const;

			Quaternion& set(Real w, Real x, Real y, Real z);

			void setAngleAxis(const Angle& angle, Vector3 axis);
			void getAngleAxis(Angle& angle, Vector3& axis) const;

			Real dotProduct(const Quaternion& q) const;
			Quaternion slerpTo(Quaternion q, Real amount, bool shortestPath) const;

			Quaternion operator+() const;
			Quaternion operator-() const;
			Quaternion& operator=(const Quaternion& q);
			Quaternion operator+(const Quaternion& q) const;
			Quaternion operator-(const Quaternion& q) const;
			Quaternion operator*(const Quaternion& q) const;
			Quaternion operator*(Real scalar) const;
			Quaternion operator/(Real scalar) const;
			Vector3 operator*(const Vector3& vector) const;
			Quaternion& operator+=(const Quaternion& q);
			Quaternion& operator-=(const Quaternion& q);
			Quaternion& operator*=(const Quaternion& q);
			Quaternion& operator*=(Real scalar);
			Quaternion& operator/=(Real scalar);

			Quaternion getInverseRotation() const;

			friend Quaternion operator*(Real scalar, const Quaternion& q);
			friend Vector3 operator*(const Vector3& vector, const Quaternion& q);
			friend std::ostream& operator<<(std::ostream& o, const Quaternion& q);

		private:
			Real m_w, m_x, m_y, m_z;

	};

	inline
	Quaternion::Quaternion()
	          : m_w(1)
	          , m_x(0)
	          , m_y(0)
	          , m_z(0)
	{}

	inline
	Quaternion::Quaternion(Real w, Real x, Real y, Real z)
	          : m_w(w)
	          , m_x(x)
	          , m_y(y)
	          , m_z(z)
	{}

	inline
	Quaternion::Quaternion(const Quaternion& q)
	          : m_w(q.m_w)
	          , m_x(q.m_x)
	          , m_y(q.m_y)
	          , m_z(q.m_z)
	{}

	inline
	Quaternion::Quaternion(const Angle& angle, const Vector3& axis)
	{
		setAngleAxis(angle, axis);
	}

	inline Real
	Quaternion::w() const
	{
		return m_w;
	}

	inline Real
	Quaternion::x() const
	{
		return m_x;
	}

	inline Real
	Quaternion::y() const
	{
		return m_y;
	}

	inline Real
	Quaternion::z() const
	{
		return m_z;
	}

	inline Quaternion&
	Quaternion::set(Real w, Real x, Real y, Real z)
	{
		m_w = w;
		m_x = x;
		m_y = y;
		m_z = z;
		return *this;
	}

	inline Real
	Quaternion::dotProduct(const Quaternion& q) const
	{
		return m_w * q.m_w + m_x * q.m_x + m_y * q.m_y + m_z * q.m_z;
	}

	inline Quaternion
	Quaternion::operator+() const
	{
		return *this;
	}

	inline Quaternion
	Quaternion::operator-() const
	{
		return Quaternion(-m_w, -m_x, -m_y, -m_z);
	}

	inline Quaternion&
	Quaternion::operator=(const Quaternion& q)
	{
		m_w = q.m_w;
		m_x = q.m_x;
		m_y = q.m_y;
		m_z = q.m_z;
		return *this;
	}

	inline Quaternion
	Quaternion::operator+(const Quaternion& q) const
	{
		return Quaternion(m_w + q.m_w, m_x + q.m_x, m_y + q.m_y, m_z + q.m_z);
	}

	inline Quaternion
	Quaternion::operator-(const Quaternion& q) const
	{
		return Quaternion(m_w - q.m_w, m_x - q.m_x, m_y - q.m_y, m_z - q.m_z);
	}

	inline Quaternion
	Quaternion::operator*(const Quaternion& q) const
	{
		// NOTE:  Multiplication is not generally commutative, so in most
		// cases p * q != q * p.
		return Quaternion
		(
			m_w * q.m_w - m_x * q.m_x - m_y * q.m_y - m_z * q.m_z,
			m_w * q.m_x + m_x * q.m_w + m_y * q.m_z - m_z * q.m_y,
			m_w * q.m_y + m_y * q.m_w + m_z * q.m_x - m_x * q.m_z,
			m_w * q.m_z + m_z * q.m_w + m_x * q.m_y - m_y * q.m_x
		);
	}

	inline Quaternion
	Quaternion::operator*(Real scalar) const
	{
		return Quaternion(scalar * m_w, scalar * m_x, scalar * m_y, scalar * m_z);
	}

	inline Quaternion
	Quaternion::operator/(Real scalar) const
	{
		return Quaternion(scalar / m_w, scalar / m_x, scalar / m_y, scalar / m_z);
	}

	inline Quaternion&
	Quaternion::operator+=(const Quaternion& q)
	{
		m_w += q.m_w;
		m_x += q.m_x;
		m_y += q.m_y;
		m_z += q.m_z;
		return *this;
	}

	inline Quaternion&
	Quaternion::operator-=(const Quaternion& q)
	{
		m_w -= q.m_w;
		m_x -= q.m_x;
		m_y -= q.m_y;
		m_z -= q.m_z;
		return *this;
	}

	inline Quaternion&
	Quaternion::operator*=(const Quaternion& q)
	{
		float w = m_w;
		float x = m_x;
		float y = m_y;
		float z = m_z;
		m_w = w * q.m_w - x * q.m_x - y * q.m_y - z * q.m_z;
		m_x = w * q.m_x + x * q.m_w + y * q.m_z - z * q.m_y;
		m_y = w * q.m_y + y * q.m_w + z * q.m_x - x * q.m_z;
		m_z = w * q.m_z + z * q.m_w + x * q.m_y - y * q.m_x;
		return *this;
	}

	inline Quaternion&
	Quaternion::operator*=(Real scalar)
	{
		m_w *= scalar;
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		return *this;
	}

	inline Quaternion&
	Quaternion::operator/=(Real scalar)
	{
		m_w *= scalar;
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		return *this;
	}

	inline Quaternion
	Quaternion::getInverseRotation() const
	{
		Real squaredLength = m_x * m_x + m_y * m_y + m_z * m_z;
		if (squaredLength < defaultTolerance)
		{
			throw "Cannot inverse Rotation of length 0";
		}
		return Quaternion(m_w / squaredLength, -m_x / squaredLength, -m_y / squaredLength, -m_z / squaredLength);
	}

	inline Quaternion
	operator*(Real scalar, const Quaternion& q)
	{
		return Quaternion(scalar * q.m_w, scalar * q.m_x, scalar * q.m_y, scalar * q.m_z);
	}

	inline Vector3
	operator*(const Vector3& vector, const Quaternion& q)
	{
		return q * vector;
	}

	inline std::ostream&
	operator<<(std::ostream& o, const Quaternion& q)
	{
		o << "Quaternion(" << q.m_w << ", " << q.m_x << ", " << q.m_y << ", " << q.m_z << ")";
		return o;
	}

}

#endif /* PURGE_QUATERNION_H */

