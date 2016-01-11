#ifndef TESTSCENE8_H
#define TESTSCENE8_H 1

#include "TestScene.h"

class TestScene8 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE8_H */

