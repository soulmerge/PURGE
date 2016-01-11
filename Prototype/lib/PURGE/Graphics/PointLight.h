#ifndef PURGE_POINTLIGHT_H
#define PURGE_POINTLIGHT_H 1

#include "Light.h"
#include "../Math/Real.h"

namespace PURGE
{

	class PointLight : public Light
	{

		public:
			static const int CHANGE_RANGE = 0x04;
			static PointLight* create();

			virtual PointLight* setRange(Real max) = 0;
			virtual Real getRange() const = 0;

		protected:
			PointLight();

	};

	inline
	PointLight::PointLight()
	{}

}

#endif /* PURGE_POINTLIGHT_H */

