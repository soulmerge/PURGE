#ifndef TESTSCENE11_H
#define TESTSCENE11_H 1

#include "TestScene.h"

class TestScene11 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE11_H */

