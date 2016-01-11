#ifndef PURGE_VECTOR3_H
#define PURGE_VECTOR3_H 1

#include "Real.h"
#include "Angle.h"
#include <ostream>
#include <assert.h>
#include <math.h>

#include <iostream>

namespace PURGE
{

	class Vector3
	{

		public:
			static const Vector3 UNIT_X;
			static const Vector3 UNIT_Y;
			static const Vector3 UNIT_Z;

			static Real defaultTolerance;

			Vector3();
			Vector3(const Vector3& v);
			Vector3(Real x, Real y, Real z);

			Real x() const;
			Real y() const;
			Real z() const;

			bool isZeroLength() const;
			bool isZeroLength(Real tolerance) const;

			Real length() const;
			Real squaredLength() const;
			Real dotProduct(const Vector3& vector) const;
			Vector3 crossProduct(const Vector3& rhs) const;
			Angle angleTo(Vector3 vector) const;

			Vector3& setX(Real x);
			Vector3& setY(Real y);
			Vector3& setZ(Real z);
			Vector3& set(Real x, Real y, Real z);
			Vector3& resize(Real length, Real tolerance = defaultTolerance);
			Vector3& resize(const Vector3& referenceVector, Real tolerance = defaultTolerance);
			Vector3& normalize(Real tolerance = defaultTolerance);

			Vector3& operator=(const Vector3& v);

			Vector3 operator+() const;
			Vector3 operator-() const;

			Vector3 operator+(const Vector3& v) const;
			Vector3 operator-(const Vector3& v) const;
			Vector3 operator*(Real scalar) const;
			Vector3 operator/(Real scalar) const;

			Vector3& operator+=(const Vector3& rhs);
			Vector3& operator-=(const Vector3& rhs);
			Vector3& operator*=(Real scalar);
			Vector3& operator/=(Real scalar);

			friend std::ostream& operator<<(std::ostream& o, const Vector3& v);

		private:
			Real m_x, m_y, m_z;

	};

	inline
	Vector3::Vector3()
	       : m_x(0)
	       , m_y(0)
	       , m_z(0)
	{}

	inline
	Vector3::Vector3(Real x, Real y, Real z)
	       : m_x(x)
	       , m_y(y)
	       , m_z(z)
	{}

	inline
	Vector3::Vector3(const Vector3& v)
	       : m_x(v.m_x)
	       , m_y(v.m_y)
	       , m_z(v.m_z)
	{}

	inline Real
	Vector3::x() const
	{
		return m_x;
	}

	inline Real
	Vector3::y() const
	{
		return m_y;
	}

	inline Real
	Vector3::z() const
	{
		return m_z;
	}

	inline bool
	Vector3::isZeroLength() const
	{
		return isZeroLength(defaultTolerance);
	}

	inline bool
	Vector3::isZeroLength(Real tolerance) const
	{
		Real squaredLength = (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
		return (squaredLength < (tolerance * tolerance));
	}

	inline Real
	Vector3::length() const
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	inline Real
	Vector3::squaredLength() const
	{
		return m_x * m_x + m_y * m_y + m_z * m_z;
	}

	inline Real
	Vector3::dotProduct(const Vector3& vector) const
	{
		return m_x * vector.m_x + m_y * vector.m_y + m_z * vector.m_z;
	}

	inline Vector3
	Vector3::crossProduct(const Vector3& vector) const
	{
		return Vector3(
			m_y * vector.m_z - m_z * vector.m_y,
			m_z * vector.m_x - m_x * vector.m_z,
			m_x * vector.m_y - m_y * vector.m_x
		);
	}

	inline Angle
	Vector3::angleTo(Vector3 vector) const
	{
		Vector3 normalizedThis(*this);
		normalizedThis.normalize();
		vector.normalize();
		return Radian(acos(normalizedThis.m_x * vector.m_x + normalizedThis.m_y * vector.m_y + normalizedThis.m_z * vector.m_z));
	}

	inline Vector3&
	Vector3::setX(Real x)
	{
		m_x = x;
		return *this;
	}

	inline Vector3&
	Vector3::setY(Real y)
	{
		m_y = y;
		return *this;
	}

	inline Vector3&
	Vector3::setZ(Real z)
	{
		m_z = z;
		return *this;
	}

	inline Vector3&
	Vector3::set(Real x, Real y, Real z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
		return *this;
	}

	inline Vector3&
	Vector3::resize(Real newLength, Real tolerance)
	{
		if (isZeroLength(tolerance))
		{
			throw "Cannot resize vector with length 0";
		}
		Real val = newLength / length();
		m_x *= val;
		m_y *= val;
		m_z *= val;
		return *this;
	}

	inline Vector3&
	Vector3::resize(const Vector3& referenceVector, Real tolerance)
	{
		return resize(referenceVector.length(), tolerance);
	}

	inline Vector3&
	Vector3::normalize(Real tolerance)
	{
		return resize(1, tolerance);
	}

	inline Vector3&
	Vector3::operator=(const Vector3& v)
	{
		m_x = v.m_x;
		m_y = v.m_y;
		m_z = v.m_z;
		return *this;
	}

	inline Vector3
	Vector3::operator+() const
	{
		return Vector3(*this);
	}

	inline Vector3
	Vector3::operator-() const
	{
		return Vector3(-m_x, -m_y, -m_z);
	}

	inline Vector3
	Vector3::operator+(const Vector3& v) const
	{
		return Vector3(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
	}

	inline Vector3
	Vector3::operator-(const Vector3& v) const
	{
		return Vector3(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
	}

	inline Vector3
	Vector3::operator*(Real scalar) const
	{
		return Vector3(m_x * scalar, m_y * scalar, m_z * scalar);
	}

	inline Vector3
	Vector3::operator/(Real scalar) const
	{
		assert(scalar != 0.0);
		return Vector3(m_x / scalar, m_y / scalar, m_z / scalar);
	}

	inline Vector3&
	Vector3::operator+=(const Vector3& rhs)
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		m_z += rhs.m_z;
		return *this;
	}

	inline Vector3&
	Vector3::operator-=(const Vector3& rhs)
	{
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		m_z -= rhs.m_z;
		return *this;
	}

	inline Vector3&
	Vector3::operator*=(Real scalar)
	{
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		return *this;
	}

	inline Vector3&
	Vector3::operator/=(Real scalar)
	{
		assert(scalar != 0.0);
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;
		return *this;
	}

	inline std::ostream&
	operator<<(std::ostream& o, const Vector3& v)
	{
		o << "Vector3(" << (fabs(v.m_x) < (Vector3::defaultTolerance) ? 0 : v.m_x) << ", " << (fabs(v.m_y) < (Vector3::defaultTolerance) ? 0 : v.m_y) << ", " << (fabs(v.m_z) < (Vector3::defaultTolerance) ? 0 : v.m_z) << ")";
		return o;
	}

}

#endif /* PURGE_VECTOR3_H */

