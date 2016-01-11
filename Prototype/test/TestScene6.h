#ifndef TESTSCENE6_H
#define TESTSCENE6_H 1

#include "TestScene.h"

class TestScene6 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE6_H */

