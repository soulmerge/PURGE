#ifndef POSITIONGENERATOR_H
#define POSITIONGENERATOR_H 1

#include <random>

class PositionGenerator
{

	public:
		PositionGenerator();
		void nextPosition(double& x, double& y, double& z);

	private:
		std::uniform_real_distribution<double> distribution;
		std::mt19937 engine;

};

inline
PositionGenerator::PositionGenerator()
                 : distribution(0, -1000)
{}

inline void
PositionGenerator::nextPosition(double& x, double& y, double& z)
{
	x = distribution(engine);
	y = distribution(engine);
	z = distribution(engine);
}

#endif /* POSITIONGENERATOR_H */

