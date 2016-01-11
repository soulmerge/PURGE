#ifndef TESTSCENE2_H
#define TESTSCENE2_H 1

#include "TestScene.h"

class TestScene2 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE2_H */

