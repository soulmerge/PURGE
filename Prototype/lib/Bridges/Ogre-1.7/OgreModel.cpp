#include "OgreModel.h"

#include "OgreRenderer.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		void
		OgreModel::update(int change)
		{
			throw std::string("OgreModel: unidentified change #") + boost::lexical_cast<std::string>(change);
		}

		void
		OgreModel::destroy()
		{
			// TODO: detach and delete node
		}

		void
		OgreModel::attachTo(Ogre::SceneNode* node) const
		{
			std::string name(original->getName());
			OgreRenderer* renderer(OgreRenderer::getInstance());
			Ogre::SceneManager* sceneManager(renderer->getOgreSceneManager());
			Ogre::Entity* ogreEntity;
			if (0 == name.compare("cube"))
			{
				ogreEntity = sceneManager->createEntity(renderer->createUniqueString("cube-Entity"), "cube");
			}
			else
			{
				ogreEntity = sceneManager->createEntity(renderer->createUniqueString(name + "-Entity"), name + ".mesh");
			}
			if (!PURGE::CoordinateSystem::get().isLeftHanded())
			{
				node->attachObject(ogreEntity);
			}
			else
			{
				Ogre::SceneNode* modelNode = node->createChildSceneNode(name + "-Node");
				modelNode->setScale(1, 1, -1);
				modelNode->attachObject(ogreEntity);
			}
		}

	}

}

