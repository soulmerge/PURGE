#ifndef TESTSCENE12_H
#define TESTSCENE12_H 1

#include "TestScene.h"

class TestScene12 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE12_H */

