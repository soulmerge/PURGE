#ifndef PURGE_LIGHT_H
#define PURGE_LIGHT_H 1

#include "../classes.h"
#include "Color.h"

namespace PURGE
{

	class Light
	{

		public:
			static const int CHANGE_ENABLED = 0x01;
			static const int CHANGE_COLOR = 0x02;
			virtual ~Light();

			Light* enable();
			Light* disable();

			virtual Light* toggle() = 0;
			virtual bool isEnabled() const = 0;

			virtual Color getColor() const = 0;
			virtual Light* setColor(Color color) = 0;

	};

	inline
	Light::~Light()
	{}

	inline Light*
	Light::enable()
	{
		if (!isEnabled())
		{
			toggle();
		}
		return this;
	}

	inline Light*
	Light::disable()
	{
		if (isEnabled())
		{
			toggle();
		}
		return this;
	}

}

#endif /* PURGE_LIGHT_H */

