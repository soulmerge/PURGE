#ifndef TESTSCENE9_H
#define TESTSCENE9_H 1

#include "TestScene.h"

class TestScene9 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE9_H */

