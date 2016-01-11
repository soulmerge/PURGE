#ifndef PURGE_SPOTLIGHT_H
#define PURGE_SPOTLIGHT_H 1

#include "Light.h"
#include "../Math/Angle.h"

namespace PURGE
{

	class SpotLight : public Light
	{

		public:
			static const int CHANGE_ANGLE = 0x04;
			static const int CHANGE_RANGE = 0x08;
			static SpotLightNode* create();

			virtual SpotLight* setHalfAngle(Angle a);
			virtual SpotLight* setFullAngle(Angle a) = 0;
			virtual Angle getHalfAngle() const;
			virtual Angle getFullAngle() const = 0;

			virtual SpotLight* setRange(Real max) = 0;
			virtual Real getRange() const = 0;

		protected:
			SpotLight();

	};

	inline
	SpotLight::SpotLight()
	{}

	inline SpotLight*
	SpotLight::setHalfAngle(Angle a)
	{
		return setFullAngle(a * 2);
	}

	inline Angle
	SpotLight::getHalfAngle() const
	{
		return getFullAngle() / 2;
	}

}

#endif /* PURGE_SPOTLIGHT_H */

