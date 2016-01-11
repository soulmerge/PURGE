#ifndef TESTSCENE3_H
#define TESTSCENE3_H 1

#include "TestScene.h"

class TestScene3 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE3_H */

