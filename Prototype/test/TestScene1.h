#ifndef TESTSCENE1_H
#define TESTSCENE1_H 1

#include "TestScene.h"

class TestScene1 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE1_H */

