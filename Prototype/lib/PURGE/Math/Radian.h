#ifndef PURGE_RADIAN_H
#define PURGE_RADIAN_H 1

#include "Angle.h"

namespace PURGE
{

	class Radian : public Angle
	{
		public:
			explicit Radian(Real value = 0);
	};

	inline
	Radian::Radian(Real value)
	{
		rad = value;
	}

}

#endif /* PURGE_RADIAN_H */

