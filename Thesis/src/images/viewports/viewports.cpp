#include <OGRE/Ogre.h>
#include <iostream>

int main() {
    Ogre::Root* root = new Ogre::Root();
    root->addResourceLocation("/home/soulmerge/projects/Diplomarbeit/Prototype/resources/Ogre/", "FileSystem");
    if (!root->restoreConfig() && !root->showConfigDialog()) {
        throw 1;
    }
    root->initialise(false);
    Ogre::SceneManager* sceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
    sceneMgr->setAmbientLight(Ogre::ColourValue::White * 10);
    Ogre::RenderWindow* window = root->createRenderWindow("Ogre RenderWindow", 800, 600, false, NULL);
    Ogre::Camera* cam1 = sceneMgr->createCamera("cam1");
    Ogre::Camera* cam2 = sceneMgr->createCamera("cam2");
    Ogre::Camera* cam3 = sceneMgr->createCamera("cam3");
    Ogre::Camera* cam4 = sceneMgr->createCamera("cam4");
	Ogre::Viewport* vp1 = window->addViewport(cam1, 1, 0  , 0  , 0.5, 0.5);
	Ogre::Viewport* vp2 = window->addViewport(cam2, 2, 0.5, 0  , 0.5, 0.5);
	Ogre::Viewport* vp3 = window->addViewport(cam3, 3, 0  , 0.5, 0.5, 0.5);
	Ogre::Viewport* vp4 = window->addViewport(cam4, 4, 0.5, 0.5, 0.5, 0.5);
    vp1->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    vp2->setBackgroundColour(Ogre::ColourValue(1, 1, 1) * 0.95);
    vp3->setBackgroundColour(Ogre::ColourValue(1, 1, 1) * 0.95);
    vp4->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    Ogre::Entity* model = sceneMgr->createEntity("model", "alexandria.mesh");
    Ogre::SceneNode* modelNode1 = sceneMgr->getRootSceneNode()->createChildSceneNode("modelnode1");
    modelNode1->attachObject(model);
    cam1->setNearClipDistance(5);
    cam2->setNearClipDistance(5);
    cam3->setNearClipDistance(5);
    cam4->setNearClipDistance(5);
	/*
    cam1->setPolygonMode(Ogre::PM_WIREFRAME);
    cam2->setPolygonMode(Ogre::PM_WIREFRAME);
    cam3->setPolygonMode(Ogre::PM_WIREFRAME);
    cam4->setPolygonMode(Ogre::PM_WIREFRAME);
	*/
    Ogre::SceneNode* camNode1 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode1");
    Ogre::SceneNode* camNode2 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode2");
    Ogre::SceneNode* camNode3 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode3");
    Ogre::SceneNode* camNode4 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode4");
    camNode1->attachObject(cam1);
    camNode2->attachObject(cam2);
    camNode3->attachObject(cam3);
    camNode4->attachObject(cam4);
	Ogre::Quaternion q;
	q.FromAngleAxis(Ogre::Degree(90), Ogre::Vector3::UNIT_Y);
	camNode1->lookAt(Ogre::Vector3(-1, -1, -1), Ogre::Node::TS_LOCAL);
	camNode2->setOrientation(q * camNode1->getOrientation());
	camNode3->setOrientation(q * camNode2->getOrientation());
	camNode4->setOrientation(q * camNode3->getOrientation());
    camNode1->setPosition(100, 100, 100);
    camNode2->setPosition(100, 100, -100);
    camNode3->setPosition(-100, 100, -100);
    camNode4->setPosition(-100, 100, 100);
    while(true) {
        Ogre::WindowEventUtilities::messagePump();
        if (window->isClosed()) {
            return 0;
        }
        if (!root->renderOneFrame()) {
            return 0;
        }
    }
    return 0;
}

