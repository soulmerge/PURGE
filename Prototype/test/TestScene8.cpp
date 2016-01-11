#include "TestScene8.h"

#include <PURGE/include.h>
#include <Bridges/Ogre-1.7/OgreRenderer.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

void
TestScene8::runPURGE()
{
	// initialize framework
	PURGEBridge::Ogre_1_7::OgreRenderer::createInstance("./resources/Ogre");
	// open window
	PURGE::Window::create(800, 600);
	// adjust camera
	PURGE::Camera::create()
		->move(PURGE::Vector3(100, 100, 100))
		->setDirection(PURGE::Vector3(-1, -1, -1));
	// load & integrate model
	for (int i = 0; i < 1000; i++)
	{
		PURGE::ModelNode::create(PURGE::ModelDefinition::load("cube"));
	}
	// loop
	runPURGELoop();
}

#include "../lib/Bridges/Ogre-1.7/sphinx/archives/Geometrik/Mesh_Cube.h"

void
TestScene8::runOgre()
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
	camNode1->setPosition(Ogre::Vector3(100, 100, 100));
	camNode1->lookAt(Ogre::Vector3(-1, -1, -1), Ogre::Node::TS_LOCAL);
	window->addViewport(cam1);
	// load & integrate model
	root->addResourceLocation("./resources/Ogre", "FileSystem");
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	Mesh_Cube M(1);
	M.createMesh("cube");
	for (int i = 0; i < 10; i++)
	{
		auto model = sceneMgr->createEntity(std::string("model") + boost::lexical_cast<std::string>(i), "cube");
		sceneMgr->getRootSceneNode()->attachObject(model);
	}
	// loop
	runOgreLoop(root);
}

void
TestScene8::runPanda(int argc, char** argv)
{
	throw "no panda implementation for this test";
}

void
TestScene8::runOsg()
{
	throw "no osg implementation for this test";
}

