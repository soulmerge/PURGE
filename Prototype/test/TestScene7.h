#ifndef TESTSCENE7_H
#define TESTSCENE7_H 1

#include "TestScene.h"

class TestScene7 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE7_H */

