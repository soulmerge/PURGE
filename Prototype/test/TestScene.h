#ifndef TESTSCENE_H
#define TESTSCENE_H 1

#include <OGRE/Ogre.h>
#include <osgViewer/Viewer>

class TestScene
{

	public:
		virtual void runPURGE() = 0;
		virtual void runOgre() = 0;
		virtual void runOsg() = 0;
		virtual void runPanda(int argc, char** argv) = 0;

	protected:
		void registerPURGEListeners();
		void registerOgreListeners(Ogre::Root* root);
		void registerPandaListeners();

		void runPURGELoop();
		void runOgreLoop(Ogre::Root* root);
		void runOsgLoop(osgViewer::Viewer* viewer);
		void runPandaLoop();

};

#endif /* TESTSCENE_H */

