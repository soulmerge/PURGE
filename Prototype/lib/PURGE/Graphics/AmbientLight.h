#ifndef PURGE_AMBIENTLIGHT_H
#define PURGE_AMBIENTLIGHT_H 1

#include "../classes.h"
#include "Light.h"

namespace PURGE
{

	class AmbientLight : public virtual Light
	{

		public:
			static AmbientLight* get();

			Light* toggle();
			bool isEnabled() const;

			Color getColor() const;
			Light* setColor(Color color);

		private:
			static AmbientLight* instance;

			AmbientLight();

			Color color;
			bool enabled;

	};

	inline
	AmbientLight::AmbientLight()
	            : color(Color::rgb(1, 1, 1))
	            , enabled(true)
	{}

	inline AmbientLight*
	AmbientLight::get()
	{
		return instance;
	}

	inline Light*
	AmbientLight::toggle()
	{
		enabled = !enabled;
		return this;
	}

	inline bool
	AmbientLight::isEnabled() const
	{
		return enabled;
	}

	inline Color
	AmbientLight::getColor() const
	{
		return color;
	}

	inline Light*
	AmbientLight::setColor(Color color)
	{
		this->color = color;
		return this;
	}

}

#endif /* PURGE_AMBIENTLIGHT_H */

