#ifndef PURGE_DEGREE_H
#define PURGE_DEGREE_H 1

#include "Angle.h"

namespace PURGE
{

	class Degree : public Angle
	{
		public:
			explicit Degree(Real value = 0);
	};

	inline
	Degree::Degree(Real value)
	      : Angle(value)
	{}

}

#endif /* PURGE_DEGREE_H */

