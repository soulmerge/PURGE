#include <OGRE/Ogre.h>
#include <iostream>
#include "sphinx/archives/Geometrik/Mesh_Cube.h"
#include "sphinx/archives/Geometrik/Mesh_Sphere.h"

int main() {
    Ogre::Root* root = new Ogre::Root();
    root->addResourceLocation("/home/soulmerge/projects/Diplomarbeit/Prototype/resources/Ogre/", "FileSystem");
    if (!root->restoreConfig() && !root->showConfigDialog()) {
        throw 1;
    }
    root->initialise(false);
    Ogre::SceneManager* sceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
    Ogre::RenderWindow* window = root->createRenderWindow("Ogre RenderWindow", 1600, 600, false, NULL);
    Ogre::Camera* cam1 = sceneMgr->createCamera("cam1");
    Ogre::Camera* cam2 = sceneMgr->createCamera("cam2");
    Ogre::Camera* cam3 = sceneMgr->createCamera("cam3");
    Ogre::Camera* cam4 = sceneMgr->createCamera("cam4");
    Ogre::Camera* cam5 = sceneMgr->createCamera("cam5");
    Ogre::Camera* cam6 = sceneMgr->createCamera("cam6");
    Ogre::Camera* cam7 = sceneMgr->createCamera("cam7");
    Ogre::Camera* cam8 = sceneMgr->createCamera("cam8");
    Ogre::Camera* cam9 = sceneMgr->createCamera("cam9");
    sceneMgr->setAmbientLight(Ogre::ColourValue::Black);
    Ogre::Viewport* vp1 = window->addViewport(cam1, 1, 0   , 0  , 0.249, 0.498);
    Ogre::Viewport* vp2 = window->addViewport(cam2, 2, 0.25, 0  , 0.249, 0.498);
    Ogre::Viewport* vp3 = window->addViewport(cam3, 3, 0.5 , 0  , 0.249, 0.498);
    Ogre::Viewport* vp4 = window->addViewport(cam4, 4, 0.75, 0  , 0.25 , 0.498);
    Ogre::Viewport* vp5 = window->addViewport(cam5, 5, 0   , 0.5, 0.249, 0.5);
    Ogre::Viewport* vp6 = window->addViewport(cam6, 6, 0.25, 0.5, 0.249, 0.5);
    Ogre::Viewport* vp7 = window->addViewport(cam7, 7, 0.5 , 0.5, 0.249, 0.5);
    Ogre::Viewport* vp8 = window->addViewport(cam8, 8, 0.75, 0.5, 0.25 , 0.5);
    // Ogre::Viewport* vp9 = window->addViewport(cam9, 9, 0.75, 0.5, 0.248, 0.49);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    // Ogre::Entity* model = sceneMgr->createEntity("model", Ogre::SceneManager::PT_CUBE);
    // model->getSubEntity(0)->getMaterial()->setAmbient(0.5, 0.5, 0.5);
    Mesh_Cube M(5);
    M.createMesh("mesh");
    Ogre::Entity* model1 = sceneMgr->createEntity("model1", "mesh");
    // Ogre::Entity* model2 = sceneMgr->createEntity("model2", "mesh");
    Ogre::Entity* model3 = sceneMgr->createEntity("model3", Ogre::SceneManager::PT_CUBE);
    Ogre::SceneNode* modelNode1 = sceneMgr->getRootSceneNode()->createChildSceneNode("modelnode1");
    // Ogre::SceneNode* modelNode2 = sceneMgr->getRootSceneNode()->createChildSceneNode("modelnode2");
    Ogre::SceneNode* modelNode3 = sceneMgr->getRootSceneNode()->createChildSceneNode("modelnode3");
    vp1->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    vp2->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    vp3->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    vp4->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    vp5->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    vp6->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    vp7->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    vp8->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    // vp9->setBackgroundColour(Ogre::ColourValue(1, 1, 1));
    modelNode1->attachObject(model1);
    modelNode1->setScale(0.5, 3, 0.5);
    // modelNode2->attachObject(model2);
    // modelNode2->setScale(0.5, 3, 0.5);
    // modelNode2->setPosition(0, 0, -5);
    modelNode3->attachObject(model3);
    modelNode3->setScale(0.001, 0.001, 5);
    modelNode3->setPosition(0, 0, 0);
    cam1->setPolygonMode(Ogre::PM_WIREFRAME);
    cam2->setPolygonMode(Ogre::PM_WIREFRAME);
    cam3->setPolygonMode(Ogre::PM_WIREFRAME);
    cam4->setPolygonMode(Ogre::PM_WIREFRAME);
    cam5->setPolygonMode(Ogre::PM_WIREFRAME);
    cam6->setPolygonMode(Ogre::PM_WIREFRAME);
    cam7->setPolygonMode(Ogre::PM_WIREFRAME);
    cam8->setPolygonMode(Ogre::PM_WIREFRAME);
    cam9->setPolygonMode(Ogre::PM_WIREFRAME);
    cam1->setNearClipDistance(5);
    cam2->setNearClipDistance(5);
    cam3->setNearClipDistance(5);
    cam4->setNearClipDistance(5);
    cam5->setNearClipDistance(5);
    cam6->setNearClipDistance(5);
    cam7->setNearClipDistance(5);
    cam8->setNearClipDistance(5);
    cam9->setNearClipDistance(5);
    Ogre::SceneNode* camNode1 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode1");
    Ogre::SceneNode* camNode2 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode2");
    Ogre::SceneNode* camNode3 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode3");
    Ogre::SceneNode* camNode4 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode4");
    Ogre::SceneNode* camNode5 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode5");
    Ogre::SceneNode* camNode6 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode6");
    Ogre::SceneNode* camNode7 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode7");
    Ogre::SceneNode* camNode8 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode8");
    Ogre::SceneNode* camNode9 = sceneMgr->getRootSceneNode()->createChildSceneNode("camnode9");
    camNode1->attachObject(cam1);
    camNode2->attachObject(cam2);
    camNode3->attachObject(cam3);
    camNode4->attachObject(cam4);
    camNode5->attachObject(cam5);
    camNode6->attachObject(cam6);
    camNode7->attachObject(cam7);
    camNode8->attachObject(cam8);
    camNode9->attachObject(cam9);
    camNode1->setPosition(25, 55, 0);
    camNode2->setPosition(25, 55, 0);
    camNode3->setPosition(25, 55, 0);
    camNode4->setPosition(25, 55, 0);
    camNode5->setPosition(25, 55, 0);
    camNode6->setPosition(25, 55, 0);
    camNode7->setPosition(25, 55, 0);
    camNode8->setPosition(25, 55, 0);
    camNode9->setPosition(10, 10, 50);
    camNode1->yaw(Ogre::Degree(60));
    camNode2->yaw(Ogre::Degree(60));
    camNode3->yaw(Ogre::Degree(60));
    camNode4->yaw(Ogre::Degree(60));
    camNode5->yaw(Ogre::Degree(60));
    camNode6->yaw(Ogre::Degree(60));
    camNode7->yaw(Ogre::Degree(60));
    camNode8->yaw(Ogre::Degree(60));
    camNode1->pitch(Ogre::Degree(-65));
    camNode2->pitch(Ogre::Degree(-65));
    camNode3->pitch(Ogre::Degree(-65));
    camNode4->pitch(Ogre::Degree(-65));
    camNode5->pitch(Ogre::Degree(-65));
    camNode6->pitch(Ogre::Degree(-65));
    camNode7->pitch(Ogre::Degree(-65));
    camNode8->pitch(Ogre::Degree(-65));
    camNode2->yaw(Ogre::Degree(24), Ogre::Node::TransformSpace(2));
    camNode3->yaw(Ogre::Degree(38), Ogre::Node::TransformSpace(2));
    camNode4->yaw(Ogre::Degree(52), Ogre::Node::TransformSpace(2));
    camNode6->yaw(Ogre::Degree(20), Ogre::Node::TransformSpace(0));
    camNode7->yaw(Ogre::Degree(30), Ogre::Node::TransformSpace(0));
    camNode8->yaw(Ogre::Degree(40), Ogre::Node::TransformSpace(0));
    // sceneMgr->setSkyBox(true, "sky");
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

