#include "TestScene2.h"

#include <pandaFramework.h>
#include <pandaSystem.h>

void
TestScene2::runPanda(int argc, char** argv)
{
	PandaFramework framework;
	framework.open_framework(argc, argv);
	WindowProperties windowProp;
	framework.get_default_window_props(windowProp);
	windowProp.set_size(800, 600);
	framework.open_window(windowProp, GraphicsPipe::BF_require_window);
	framework.main_loop();
}

#include <PURGE/include.h>
#include <Bridges/Ogre-1.7/OgreRenderer.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

void
TestScene2::runPURGE()
{
	PURGEBridge::Ogre_1_7::OgreRenderer::createInstance("./resources/Ogre");
	PURGE::Window::create(800, 600);
	runPURGELoop();
}

void
TestScene2::runOgre()
{
	Ogre::Root* root = new Ogre::Root();
	root->restoreConfig();
	root->initialise(false);
	auto window = root->createRenderWindow("Ogre RenderWindow", 800, 600, false);
	auto sceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
	auto cam1 = sceneMgr->createCamera("cam1");
	sceneMgr->getRootSceneNode()->attachObject(cam1);
	window->addViewport(cam1);
	runOgreLoop(root);
}

#include <osg/Node>
#include <osgDB/ReadFile> 
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>

void
TestScene2::runOsg()
{
	auto viewer = new osgViewer::Viewer();
	viewer->setUpViewInWindow(560, 240, 800, 600); 
	runOsgLoop(viewer);
}

