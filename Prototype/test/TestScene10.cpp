#include "TestScene10.h"

#include <PURGE/include.h>
#include <Bridges/Ogre-1.7/OgreRenderer.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#define ROWS 32
#define COLS 24
#define WIDTH ((190 / ROWS) * ROWS)
#define HEIGHT ((140 / COLS) * COLS)
#define LEFT(i) ((i % ROWS) * (WIDTH / ROWS) - WIDTH / 2 + (ROWS % 2 ? 0 : (WIDTH / ROWS / 2)))
#define UP(i) ((i / ROWS) * (HEIGHT / COLS) - HEIGHT / 2 + (COLS % 2 ? 0 : (HEIGHT / COLS / 2)))

void
TestScene10::runPURGE()
{
	// initialize framework
	PURGEBridge::Ogre_1_7::OgreRenderer::createInstance("./resources/Ogre");
	// open window
	PURGE::Window::create(800, 600);
	// adjust camera
	auto camera = PURGE::Camera::create()
		->move(PURGE::Vector3(100, 100, 100))
		->setDirection(PURGE::Vector3(-1, -1, -1));
	// load & integrate model
	auto task = PURGE::SceneNodeModificationTask::create()
		->rotate(PURGE::Degree(360 / 5), PURGE::CoordinateSystem::get().getUpVector());
	PURGE::MainTaskGroup::get()->add(task);
	for (int i = 0; i < ROWS * COLS; i++)
	{
		task->registerNode(
			PURGE::ModelNode::create(PURGE::ModelDefinition::load("cube"))
				->move(LEFT(i), UP(i), 0, camera)
		);
	}
	// loop
	runPURGELoop();
}

#include "../lib/Bridges/Ogre-1.7/sphinx/archives/Geometrik/Mesh_Cube.h"

class MoveObjectTask_Ogre10 : public Ogre::FrameListener
{
	public:
		MoveObjectTask_Ogre10(std::list<Ogre::SceneNode*> nodes) : nodes(nodes) {}
		bool frameEnded(const Ogre::FrameEvent &evt)
		{
			Ogre::Quaternion q;
			q.FromAngleAxis(Ogre::Degree(360 * ((float) timer.getMilliseconds()) / 5000), Ogre::Vector3(0, 1, 0));
			for (auto node = nodes.begin(); node != nodes.end(); node++)
			{
				(*node)->setOrientation(q);
			}
			return true;
		}
	private:
		std::list<Ogre::SceneNode*> nodes;
		Ogre::Timer timer;
};

void
TestScene10::runOgre()
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
	std::list<Ogre::SceneNode*> nodes;
	for (int i = 0; i < ROWS * COLS; i++)
	{
		auto node = sceneMgr->getRootSceneNode()->createChildSceneNode();
		node->attachObject(sceneMgr->createEntity(std::string("model") + boost::lexical_cast<std::string>(i), "cube"));
		node->setPosition(
			camNode1->getOrientation() * -Ogre::Vector3::UNIT_X * LEFT(i)
			+ camNode1->getOrientation() * Ogre::Vector3::UNIT_Y * UP(i)
		);
		nodes.push_back(node);
	}
	root->addFrameListener(new MoveObjectTask_Ogre10(nodes));
	// loop
	runOgreLoop(root);
}

void
TestScene10::runPanda(int argc, char** argv)
{
	throw "no panda implementation for this test";
}

void
TestScene10::runOsg()
{
	throw "no osg implementation for this test";
}

