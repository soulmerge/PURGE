#include "TestScene3.h"

#include <pandaFramework.h>
#include <pandaSystem.h>

void
TestScene3::runPanda(int argc, char** argv)
{
	// initialize framework
	PandaFramework framework;
	framework.open_framework(argc, argv);
	// open window
	WindowProperties windowProp;
	framework.get_default_window_props(windowProp);
	windowProp.set_size(800, 600);
	auto window = framework.open_window(windowProp, GraphicsPipe::BF_require_window);
	// adjust camera
	auto camera = window->get_camera_group();
	camera.set_pos(2000, -2000, 2000);
	camera.look_at(0, 0, 0);
	// loop
	framework.main_loop();
}

#include <PURGE/include.h>
#include <Bridges/Ogre-1.7/OgreRenderer.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

void
TestScene3::runPURGE()
{
	// initialize framework
	PURGEBridge::Ogre_1_7::OgreRenderer::createInstance("./resources/Ogre");
	// open window
	PURGE::Window::create(800, 600);
	// adjust camera
	PURGE::Camera::create()
		->move(100, 100, 100)
		->setDirection(-1, -1, -1);
	// loop
	runPURGELoop();
}

void
TestScene3::runOgre()
{
	// initialize framework & open window
	Ogre::Root* root = new Ogre::Root();
	root->restoreConfig();
	root->initialise(false);
	auto window = root->createRenderWindow("Ogre RenderWindow", 800, 600, false);
	auto sceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
	// adjust camera
	auto cam1 = sceneMgr->createCamera("cam1");
	auto camNode1 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode1");
	cam1->setNearClipDistance(5);
	camNode1->attachObject(cam1);
	camNode1->setPosition(100, 100, 100);
	camNode1->lookAt(Ogre::Vector3(-1, -1, -1), Ogre::Node::TS_LOCAL);
	window->addViewport(cam1);
	// loop
	runOgreLoop(root);
}

#include <osg/Node>
#include <osgDB/ReadFile> 
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>

void
TestScene3::runOsg()
{
	// open window
	auto viewer = new osgViewer::Viewer();
	viewer->setUpViewInWindow(560, 240, 800, 600); 
	// adjust camera
	auto camera = viewer->getCamera();
	camera->setViewMatrixAsLookAt(osg::Vec3d(100, 100, 100), osg::Vec3d(0, 0, 0), osg::Vec3d(0, 1, 0));
	// loop
	runOsgLoop(viewer);
}

