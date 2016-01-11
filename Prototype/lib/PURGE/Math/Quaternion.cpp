// NOTE THAT THIS FILE IS BASED ON MATERIAL FROM:

// Magic Software, Inc.
// http://www.geometrictools.com
// Copyright (c) 2000, All Rights Reserved
//
// Source code from Magic Software is supplied under the terms of a license
// agreement and may not be copied or disclosed except in accordance with the
// terms of that agreement.  The various license agreements may be found at
// the Magic Software web site.  This file is subject to the license
//
// FREE SOURCE CODE
// http://www.geometrictools.com/License/WildMagic3License.pdf

#include "Quaternion.h"
#include <math.h>
#include <assert.h>

namespace PURGE
{

	const Real
	Quaternion::defaultTolerance = 1e-06;

	const Quaternion
	Quaternion::ZERO(0.0, 0.0, 0.0, 0.0);

	const Quaternion
	Quaternion::IDENTITY(1.0, 0.0, 0.0, 0.0);

	void
	Quaternion::setAngleAxis(const Angle& angle, Vector3 axis)
	{
		axis.normalize();
		// The quaternion representing the rotation is
		//   q = cos(A / 2) + sin(A / 2) * (x * i + y * j + z * k)
		Angle halfAngle(angle / 2);
		Real sinHalfAngle = sin(halfAngle.radians());
		m_w = cos(halfAngle.radians());
		m_x = sinHalfAngle * axis.x();
		m_y = sinHalfAngle * axis.y();
		m_z = sinHalfAngle * axis.z();
	}

	void
	Quaternion::getAngleAxis(Angle& angle, Vector3& axis) const
	{
		// The quaternion representing the rotation is
		//   q = cos(A / 2) + sin(A / 2) * (x * i + y * j + z * k)
		Real squaredLength = m_x * m_x + m_y * m_y + m_z * m_z;
		if (squaredLength > 0.0)
		{
			angle = 2.0 * acos(m_w);
			Real length = sqrt(squaredLength);
			axis.set(m_x / length, m_y / length, m_z / length);
		}
		else
		{
			// angle is 0 (mod 2 * pi), so any axis will do
			angle = Angle(0.0);
			axis.set(1.0, 0.0, 0.0);
		}
	}

	Quaternion
	Quaternion::slerpTo(Quaternion q, Real amount, bool shortestPath) const
	{
		assert(fabs(amount) <= 1.0);
		float angle = acosf(dotProduct(q));
		if (fabsf(angle) == 0.0)
		{
			return *this;
		}
        if (angle < 0.0 && shortestPath)
        {
            angle = -angle;
            q = -q;
        }
		float sn = sinf(angle);
		float tAngle = amount * angle;
		float coeff0 = sinf(angle - tAngle) / sn;
		float coeff1 = sinf(tAngle) / sn;
		return coeff0 * *this + coeff1 * q;
	}

	Vector3
	Quaternion::operator*(const Vector3& v) const
	{
		// nVidia SDK implementation
		Vector3 uv, uuv;
		Vector3 qvec(m_x, m_y, m_z);
		uv = qvec.crossProduct(v);
		uuv = qvec.crossProduct(uv);
		uv *= (2.0f * m_w);
		uuv *= 2.0f;
		return v + uv + uuv;
	}

}

