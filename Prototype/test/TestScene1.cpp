#include "TestScene1.h"

#include <pandaFramework.h>
#include <pandaSystem.h>

void
TestScene1::runPanda(int argc, char** argv)
{
	PandaFramework framework;
	framework.open_framework(argc, argv);
	framework.open_window();
	framework.main_loop();
}

#include <PURGE/include.h>
#include <Bridges/Ogre-1.7/OgreRenderer.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

void
TestScene1::runPURGE()
{
	PURGEBridge::Ogre_1_7::OgreRenderer::createInstance("./resources/Ogre");
	PURGE::MainTaskGroup::get()->loop();
}

void
TestScene1::runOgre()
{
	Ogre::Root* root = new Ogre::Root();
	root->restoreConfig();
	auto window = root->initialise(true);
	auto sceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
	auto cam1 = sceneMgr->createCamera("cam1");
	sceneMgr->getRootSceneNode()->attachObject(cam1);
	window->addViewport(cam1);
	root->startRendering();
}

#include <osg/Node>
#include <osgDB/ReadFile> 
#include <osgViewer/Viewer>

void
TestScene1::runOsg()
{
	osgViewer::Viewer().run();
}

