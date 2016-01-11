#ifndef TESTSCENE4_H
#define TESTSCENE4_H 1

#include "TestScene.h"

class TestScene4 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE4_H */

