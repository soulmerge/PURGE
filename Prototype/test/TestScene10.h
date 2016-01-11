#ifndef TESTSCENE10_H
#define TESTSCENE10_H 1

#include "TestScene.h"

class TestScene10 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE10_H */

