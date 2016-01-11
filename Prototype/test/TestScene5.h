#ifndef TESTSCENE5_H
#define TESTSCENE5_H 1

#include "TestScene.h"

class TestScene5 : public TestScene
{

	public:
		void runPURGE();
		void runOgre();
		void runOsg();
		void runPanda(int argc, char** argv);

};

#endif /* TESTSCENE5_H */

