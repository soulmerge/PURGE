#ifndef PURGE_SPOTLIGHTDEFINITION_H
#define PURGE_SPOTLIGHTDEFINITION_H 1

#include "SpotLight.h"
#include "../TrackedObject.h"

namespace PURGE
{

	class SpotLightDefinition : public virtual SpotLight, public virtual TrackedObject<SpotLightDefinition>
	{

		public:
			static SpotLightDefinition* create();

			Light* toggle();
			bool isEnabled() const;

			Color getColor() const;
			Light* setColor(Color color);

			SpotLight* setFullAngle(Angle a);
			Angle getFullAngle() const;

			SpotLight* setRange(Real max);
			Real getRange() const;

		private:
			SpotLightDefinition();

			Color color;
			bool enabled;
			Angle fullAngle;
			Real range;

	};

	inline SpotLightDefinition*
	SpotLightDefinition::create()
	{
		return new SpotLightDefinition();
	}

	inline
	SpotLightDefinition::SpotLightDefinition()
	                   : color(Color::WHITE)
	                   , enabled(true)
	                   , fullAngle(45)
	                   , range(REAL_MAX)
	{
		init();
	}

	inline Light*
	SpotLightDefinition::toggle()
	{
		enabled = !enabled;
		markChanged(CHANGE_ENABLED);
		return this;
	}

	inline bool
	SpotLightDefinition::isEnabled() const
	{
		return enabled;
	}

	inline Color
	SpotLightDefinition::getColor() const
	{
		return color;
	}

	inline Light*
	SpotLightDefinition::setColor(Color color)
	{
		this->color = color;
		markChanged(CHANGE_COLOR);
		return this;
	}

	inline SpotLight*
	SpotLightDefinition::setFullAngle(Angle angle)
	{
		this->fullAngle = angle;
		markChanged(CHANGE_ANGLE);
		return this;
	}

	inline Angle
	SpotLightDefinition::getFullAngle() const
	{
		return fullAngle;
	}

	inline SpotLight*
	SpotLightDefinition::setRange(Real range)
	{
		this->range = range;
		return this;
	}

	inline Real
	SpotLightDefinition::getRange() const
	{
		return range;
	}

}

#endif /* PURGE_SPOTLIGHTDEFINITION_H */

