#ifndef PURGE_COLOR_H
#define PURGE_COLOR_H 1

namespace PURGE
{

	class Color
	{

		public:
			static Color rgb(float red, float green, float blue);

			static const Color WHITE;
			static const Color BLACK;
			static const Color RED;
			static const Color GREEN;
			static const Color BLUE;

			float getRed() const;
			float getGreen() const;
			float getBlue() const;
			Color& adjustIntensity(float value);

		private:
			Color(float red, float green, float blue);

			float red;
			float green;
			float blue;

	};

}

namespace PURGE
{

	inline Color
	Color::rgb(float red, float green, float blue)
	{
		return Color(red, green, blue);
	}

	inline
	Color::Color(float red, float green, float blue)
	     : red(red)
	     , green(green)
	     , blue(blue)
	{}

	inline float
	Color::getRed() const
	{
		return red;
	}

	inline float
	Color::getGreen() const
	{
		return green;
	}

	inline float
	Color::getBlue() const
	{
		return blue;
	}

	inline Color&
	Color::adjustIntensity(float value)
	{
		red *= value;
		green *= value;
		blue *= value;
		return *this;
	}

}

#endif /* PURGE_COLOR_H */

