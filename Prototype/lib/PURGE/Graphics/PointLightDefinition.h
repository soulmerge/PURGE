#ifndef PURGE_POINTLIGHTDEFINITION_H
#define PURGE_POINTLIGHTDEFINITION_H 1

#include "PointLight.h"
#include "../TrackedObject.h"

namespace PURGE
{

	class PointLightDefinition : public virtual PointLight, public virtual TrackedObject<PointLightDefinition>
	{

		public:
			static PointLightDefinition* create();

			Light* toggle();
			bool isEnabled() const;

			Color getColor() const;
			Light* setColor(Color color);

			PointLight* setRange(Real max);
			Real getRange() const;

		private:
			PointLightDefinition();

			Color color;
			bool enabled;
			Real range;

	};

	inline PointLightDefinition*
	PointLightDefinition::create()
	{
		return new PointLightDefinition();
	}

	inline
	PointLightDefinition::PointLightDefinition()
	                   : color(Color::WHITE)
	                   , enabled(true)
	                   , range(REAL_MAX)
	{
		init();
	}

	inline Light*
	PointLightDefinition::toggle()
	{
		enabled = !enabled;
		markChanged(CHANGE_ENABLED);
		return this;
	}

	inline bool
	PointLightDefinition::isEnabled() const
	{
		return enabled;
	}

	inline Color
	PointLightDefinition::getColor() const
	{
		return color;
	}

	inline Light*
	PointLightDefinition::setColor(Color color)
	{
		this->color = color;
		markChanged(CHANGE_COLOR);
		return this;
	}

	inline PointLight*
	PointLightDefinition::setRange(Real range)
	{
		this->range = range;
		markChanged(CHANGE_RANGE);
		return this;
	}

	inline Real
	PointLightDefinition::getRange() const
	{
		return range;
	}

}

#endif /* PURGE_POINTLIGHTDEFINITION_H */

