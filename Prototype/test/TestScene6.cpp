#include "TestScene6.h"

#include <pandaFramework.h>
#include <pandaSystem.h>

AsyncTask::DoneStatus moveObjectTask_Panda6(GenericAsyncTask* task, void* data)
{
	double time = ClockObject::get_global_clock()->get_real_time();
	float pos = -2000 + (time / 5) * 2000;
	static_cast<NodePath*>(data)->set_pos(pos, -pos, pos);
	return AsyncTask::DS_cont;
}

void
TestScene6::runPanda(int argc, char** argv)
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
	camera.look_at(LPoint3(0, 0, 0));
	// load & integrate model
	NodePath* model = new NodePath(window->load_model(framework.get_models(), "panda-model"));
	model->set_pos(1, 0, 0);
	model->reparent_to(window->get_render());
	// model movement
	AsyncTaskManager::get_global_ptr()->add(new GenericAsyncTask("Moves model towards camera", &moveObjectTask_Panda6, model));
	// loop
	framework.main_loop();
}

#include <PURGE/include.h>
#include <Bridges/Ogre-1.7/OgreRenderer.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

void
TestScene6::runPURGE()
{
	// initialize framework
	PURGEBridge::Ogre_1_7::OgreRenderer::createInstance("./resources/Ogre");
	// open window
	PURGE::Window::create(800, 600);
	// adjust camera
	PURGE::Camera::create()
		->move(100, 100, 100)
		->setDirection(-1, -1, -1);
	// load & integrate model
	auto model = PURGE::Model::load("alexandria")->move(-100, -100, -100);
	// model movement
	auto task = PURGE::SceneNodeModificationTask::create(model)->move(20, 20, 20);
	PURGE::MainTaskGroup::get()->add(task);
	// loop
	runPURGELoop();
}

class MoveObjectTask_Ogre6 : public Ogre::FrameListener
{
	public:
		MoveObjectTask_Ogre6(Ogre::SceneNode* node) : node(node) {}
		bool frameEnded(const Ogre::FrameEvent &evt)
		{
			node->setPosition(Ogre::Vector3(-100, -100, -100) * (1 - (((float) timer.getMilliseconds()) / 5000)));
			return true;
		}
	private:
		Ogre::SceneNode* node;
		Ogre::Timer timer;
};

void
TestScene6::runOgre()
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
	auto model = sceneMgr->createEntity("model", "alexandria.mesh");
	auto modelNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	modelNode->attachObject(model);
	// position model
	modelNode->setPosition(Ogre::Vector3(-100, -100, -100));
	// model movement
	root->addFrameListener(new MoveObjectTask_Ogre6(modelNode));
	// loop
	runOgreLoop(root);
}

#include <osg/Node>
#include <osgDB/ReadFile> 
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osg/Timer>

class MoveObjectTask_Osg6 : public osg::NodeCallback 
{
	public:
		MoveObjectTask_Osg6() {start_tick = osg::Timer::instance()->tick();}
		virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
		{
			auto transformer = dynamic_cast<osg::PositionAttitudeTransform*>(node);
			float scalar = osg::Timer::instance()->delta_s(start_tick, osg::Timer::instance()->tick()) / 5;
			transformer->setPosition(osg::Vec3(-100, -100, -100) * (1 - scalar));
			traverse(node, nv); 
		}
	private:
		osg::Timer_t start_tick;
};

void
TestScene6::runOsg()
{
	// open window
	auto viewer = new osgViewer::Viewer();
	viewer->setUpViewInWindow(560, 240, 800, 600); 
	// adjust camera
	auto camera = viewer->getCamera();
	camera->setViewMatrixAsLookAt(osg::Vec3d(100, 100, 100), osg::Vec3d(0, 0, 0), osg::Vec3d(0, 1, 0));
	// load & integrate model
	auto modelNode = osgDB::readNodeFile("/home/soulmerge/projects/Diplomarbeit/Prototype/resources/Ogre/alexandria.3ds");
	auto modelPositioner = new osg::PositionAttitudeTransform();
	modelPositioner->addChild(modelNode);
	modelPositioner->setPosition(osg::Vec3(-100, -100, -100));
	viewer->setSceneData(modelPositioner);
	// model movement
	modelPositioner->setUpdateCallback(new MoveObjectTask_Osg6());
	// loop
	runOsgLoop(viewer);
}

