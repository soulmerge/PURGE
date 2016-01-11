#ifndef PURGE_ANGLE_H
#define PURGE_ANGLE_H 1

#include "Real.h"
#include <math.h>
#include <ostream>

namespace PURGE
{

	class Angle
	{

		public:
			static Angle defaultTolerance;

			explicit Angle(Real degree = 0);
			Angle(const Angle& a);
			Angle& operator=(const Real& rhs);
			Angle& operator=(const Angle& rhs);

			Real degrees() const;
			Real radians() const;

			Angle operator+();
			Angle operator-() const;
			Angle operator+(const Angle& rhs) const;
			Angle operator-(const Angle& rhs) const;
			Angle operator*(Real rhs) const;
			Angle operator/(Real rhs) const;
			Angle& operator+=(const Angle& rhs);
			Angle& operator-=(const Angle& rhs);
			Angle& operator*=(Real rhs);
			Angle& operator/=(Real rhs);
			bool operator==(const Angle& rhs) const;
			bool operator!=(const Angle& rhs) const;

			bool equals(const Angle& rhs) const;
			bool equals(const Angle& rhs, const Angle& tolerance) const;

			friend Angle operator*(Real a, const Angle& b);

			friend std::ostream& operator<<(std::ostream& o, const Angle& a);

		protected:
			Real rad;

		private:
			Angle(Real rad, bool isRadian);

	};

}

#include "Radian.h"
#include "Degree.h"

namespace PURGE
{

	inline
	Angle::Angle(Real degree)
	     : rad(degree * M_PI / 180.0)
	{}

	inline 
	Angle::Angle(const Angle& a)
	     : rad(a.rad)
	{}

	inline
	Angle::Angle(Real rad, bool isRadian)
	     : rad(rad)
	{}

	inline Angle&
	Angle::operator=(const Real& rhs)
	{
		rad = rhs;
		return *this;
	}

	inline Angle&
	Angle::operator=(const Angle& rhs)
	{
		rad = rhs.rad;
		return *this;
	}

	inline Real
	Angle::degrees() const
	{
		return rad * 180.0 / M_PI;
	}

	inline Real
	Angle::radians() const
	{
		return rad;
	}

	inline Angle
	Angle::operator+()
	{
		return *this;
	}

	inline Angle
	Angle::operator-() const
	{
		return Angle(-rad, true);
	}

	inline Angle
	Angle::operator+(const Angle& rhs) const
	{
		return Angle(rad + rhs.rad, true);
	}

	inline Angle
	Angle::operator-(const Angle& rhs) const
	{
		return Angle(rad - rhs.rad, true);
	}

	inline Angle
	Angle::operator*(Real rhs) const
	{
		return Angle(rad * rhs, true);
	}

	inline Angle
	Angle::operator/(Real rhs) const
	{
		return Angle(rad / rhs, true);
	}

	inline Angle&
	Angle::operator+=(const Angle& rhs)
	{
		rad += rhs.rad;
		return *this;
	}

	inline Angle&
	Angle::operator-=(const Angle& rhs)
	{
		rad -= rhs.rad;
		return *this;
	}

	inline Angle&
	Angle::operator*=(Real rhs)
	{
		rad *= rhs;
		return *this;
	}

	inline Angle&
	Angle::operator/=(Real rhs)
	{
		rad /= rhs;
		return *this;
	}

	inline bool
	Angle::operator==(const Angle& rhs) const
	{
		return equals(rhs, defaultTolerance);
	}

	inline bool
	Angle::operator!=(const Angle& rhs) const
	{
		return !operator==(rhs);
	}

	inline bool
	Angle::equals(const Angle& rhs) const
	{
		return equals(rhs, defaultTolerance);
	}

	inline bool
	Angle::equals(const Angle& rhs, const Angle& tolerance) const
	{
		return rad < (rhs.rad + tolerance.rad)
			&& rad > (rhs.rad - tolerance.rad);
	}

	inline Angle
	operator*(Real a, const Angle& b)
	{
		return Angle(a * b.rad, true);
	}

	inline std::ostream&
	operator<<(std::ostream& o, const Angle& a)
	{
		o << "Angle(" << a.degrees() << "°)";
		return o;
	}

}

#endif /* PURGE_ANGLE_H */

