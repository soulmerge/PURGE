/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    
    // Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
 
    // Create an Entity
    Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
 
    // Create a SceneNode and attach the Entity to it
    Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
    headNode->attachObject(ogreHead);
	headNode->setPosition(0, 25, 0);
	headNode->roll(Ogre::Radian(0.5));

	Ogre::ManualObject* myManualObject =  mSceneMgr->createManualObject("manual1"); 
	Ogre::ManualObject* myManualObject2 =  mSceneMgr->createManualObject("manual2"); 
	Ogre::SceneNode* myManualObjectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("manual1_node"); 
	Ogre::SceneNode* myManualObjectNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("manual2_node"); 
	 
	// NOTE: The second parameter to the create method is the resource group the material will be added to.
	// If the group you name does not exist (in your resources.cfg file) the library will assert() and your program will crash
	Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("blueMaterial","General"); 
	myManualObjectMaterial->setReceiveShadows(false); 
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1); 

	myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("greenMaterial","General"); 
	myManualObjectMaterial->setReceiveShadows(false); 
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,1,0,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,1,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,1,0); 

	myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("redMaterial","General"); 
	myManualObjectMaterial->setReceiveShadows(false); 
	myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(1,0,0,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(1,0,0); 
	myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(1,0,0); 

	myManualObject->begin("blueMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
	myManualObject->position(0, 0, 0); 
	myManualObject->position(50, 0, 0); 
	myManualObject->end(); 
	myManualObject->begin("greenMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
	myManualObject->position(0, 0, 0); 
	myManualObject->position(0, 70, 0); 
	myManualObject->end(); 
	myManualObject->begin("redMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
	myManualObject->position(0, 0, 0); 
	myManualObject->position(0, 0, 50); 
	myManualObject->end(); 
	 
	myManualObjectNode->attachObject(myManualObject);

	myManualObject2->begin("blueMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
	myManualObject2->position(0, 0, 0); 
	myManualObject2->position(50, 0, 0); 
	myManualObject2->end(); 
	myManualObject2->begin("greenMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
	myManualObject2->position(0, 0, 0); 
	myManualObject2->position(0, 70, 0); 
	myManualObject2->end(); 
	myManualObject2->begin("redMaterial", Ogre::RenderOperation::OT_LINE_LIST); 
	myManualObject2->position(0, 0, 0); 
	myManualObject2->position(0, 0, 50); 
	myManualObject2->end(); 
	 
	myManualObjectNode2->attachObject(myManualObject2);
	myManualObjectNode2->roll(Ogre::Radian(0.5));


    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
