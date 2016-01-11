#include "TestScene.h"

#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h> 
#include <Bridges/Ogre-1.7/OgreRenderer.h>

class LifeTimeListener : public Ogre::FrameListener, public PURGE::Task
{
	public:

		LifeTimeListener() : count(0), started(false) {}

		bool frameEnded(const Ogre::FrameEvent &evt)
		{
			return check();
		}

		void perform()
		{
			if (!check()) {
				PURGE::MainTaskGroup::get()->stop();
			}
		}

		bool check()
		{
			if (!started) {
				if (root)
				{
					// printScene(root, 0);
				}
				startTime = boost::posix_time::microsec_clock::local_time();
				started = true;
				return true;
			}
			count++;
			boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
			auto time = (now - startTime).total_microseconds() / 1000000.0;
			if (time < 5.0)
			{
				return true;
			}
			struct rusage usage;
			getrusage(RUSAGE_SELF, &usage);
			printf("%10.2f %ld\n", (((float) count) / time), (usage.ru_maxrss));
			return false;
		}

		Ogre::SceneNode* root;

	private:
		int count;
		bool started;
		boost::posix_time::ptime startTime;

		void printScene(Ogre::SceneNode* node, int indent)
		{
			for (int i = 0; i < indent; i++)
			{
				std::cout << "    ";
			}
			indent++;
			std::cout
				<< node->getName()
				<< " " << node->getPosition()
				<< " " << node->getOrientation() * Ogre::Vector3(0, 0, -1)
				<< std::endl;
			auto objects = node->getAttachedObjectIterator();
			while (objects.hasMoreElements())
			{
				for (int i = 0; i < indent; i++)
				{
					std::cout << "    ";
				}
				auto object = objects.getNext();
				std::cout << object->getName();
				if (auto light = dynamic_cast<Ogre::Light*>(object))
				{
					std::cout << " " << light->getDirection() * Ogre::Vector3(0, 0, -1);
				}
				else if (auto cam = dynamic_cast<Ogre::Camera*>(object))
				{
					std::cout << " " << cam->getOrientation() * Ogre::Vector3(0, 0, -1);
				}
				std::cout << std::endl;
			}
			auto n = node->getChildIterator();
			while (n.hasMoreElements())
			{
				printScene(dynamic_cast<Ogre::SceneNode*>(n.getNext()), indent + 1);
			}
		}

};

void
TestScene::registerPURGEListeners()
{
	// PURGE::MainTaskGroup::get()->push_back(PURGE::TaskP(new LifeTimeListener()));
	PURGEBridge::Ogre_1_7::OgreRenderer::getInstance()->activate();
	auto l = new LifeTimeListener();
	l->root = PURGEBridge::Ogre_1_7::OgreRenderer::getInstance()->getOgreSceneManager()->getRootSceneNode();
	PURGEBridge::Ogre_1_7::OgreRenderer::getInstance()->getOgreRoot()->addFrameListener(l);
}

void
TestScene::registerOgreListeners(Ogre::Root* root)
{
	auto l = new LifeTimeListener();
	l->root = root->getSceneManager("SceneManagerInstance1")->getRootSceneNode();
	root->addFrameListener(l);
}

void
TestScene::runPURGELoop()
{
	registerPURGEListeners();
	PURGE::MainTaskGroup::get()->loop();
}

void
TestScene::runOgreLoop(Ogre::Root* root)
{
	registerOgreListeners(root);
	root->startRendering();
}

void
TestScene::runOsgLoop(osgViewer::Viewer* viewer)
{
	LifeTimeListener x;
	while (!viewer->done() && x.check())
	{
		viewer->frame();
	}
}

