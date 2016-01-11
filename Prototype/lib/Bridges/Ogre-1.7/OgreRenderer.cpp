#include "OgreRenderer.h"

#include "OgreWindow.h"
#include "OgreModel.h"
#include "OgreSceneNode.h"
#include "OgreCamera.h"
#include "OgreSpotLight.h"
#include "OgrePointLight.h"

#include "sphinx/archives/Geometrik/Mesh_Cube.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		OgreRenderer*
		OgreRenderer::instance = NULL;

		bool
		OgreRenderer::windowIsClosed(const PURGE::Window* window, bool currentStatus) const
		{
			auto transcript = OgreWindow::getTranscript(window);
			if (!transcript)
			{
				return currentStatus;
			}
			return transcript->getOgreWindow()->isClosed();
		}

		void
		OgreRenderer::finishRendering()
		{
			ogreRoot->getRenderSystem()->_swapAllRenderTargetBuffers(ogreRoot->getRenderSystem()->getWaitForVerticalBlank());
			for (SceneManagerEnumerator::SceneManagerIterator it = ogreRoot->getSceneManagerIterator(); it.hasMoreElements(); it.moveNext())
			{
				it.peekNextValue()->_handleLodEvents();
			}
			if (!ogreRoot->_fireFrameEnded())
			{
				PURGE::MainTaskGroup::get()->stop();
			}
		}

		void
		OgreRenderer::startRendering()
		{
			if (!fullyInitialized)
			{
				if (PURGE::Window::getAllInstances().empty())
				{
					return;
				}
				_activateInstances();
			}
			ogreSceneManager->setAmbientLight(convert(PURGE::AmbientLight::get()->getColor()));
			// Order is defined by the following facts:
			// - Ogre crashes if I do not create a window first
			// - Need to initialize stuff first that is required by the SceneNode class
			// - Need to add Viewports when Cameras and Windows have been created
			OgreWindow::updateInstances();
			OgreCamera::updateInstances();
			OgreSpotLight::updateInstances();
			OgrePointLight::updateInstances();
			OgreModel::updateInstances();
			OgreSceneNode::updateInstances();
			OgreWindow::OgreViewport::updateInstances();
			Ogre::WindowEventUtilities::messagePump();
			if (!ogreRoot->_fireFrameStarted())
			{
				PURGE::MainTaskGroup::get()->stop();
			}
			ogreRoot->getRenderSystem()->_updateAllRenderTargets(false);
			if (!ogreRoot->_fireFrameRenderingQueued())
			{
				PURGE::MainTaskGroup::get()->stop();
			}
		}

		void
		OgreRenderer::_activateInstances()
		{
			if (PURGE::Window::getAllInstances().empty())
			{
				return;
			}
			// Order is defined by the following facts:
			// - Ogre crashes if I do not create a window first
			// - Need to initialize stuff first that is required by the SceneNode class
			// - Need to add Viewports when Cameras and Windows have been created
			OgreWindow::activateInstances();
			{
				// the following steps require a Ogre::Window object.
				for (auto location = resourceLocations.begin(); location != resourceLocations.end(); location++)
				{
					ogreRoot->addResourceLocation(*location, "FileSystem");
				}
				Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
				Mesh_Cube(1).createMesh("cube");
			}
			OgreCamera::activateInstances();
			OgreSpotLight::activateInstances();
			OgrePointLight::activateInstances();
			OgreModel::activateInstances();
			OgreSceneNode::activateInstances();
			OgreWindow::OgreViewport::activateInstances();
			fullyInitialized = true;
		}

		void
		OgreRenderer::printSceneGraph() const
		{
			printHelper(ogreSceneManager->getRootSceneNode(), 0);
		}

		void
		OgreRenderer::printHelper(Ogre::SceneNode* node, int indent) const
		{
			for (int i = 0; i < indent; i++)
			{
				std::cout << "    ";
			}
			indent++;
			std::cout
				<< node->getName()
				<< " " << node->getPosition()
				<< " " << node->getOrientation() * convert(PURGE::CoordinateSystem::get().getForwardVector())
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
				if (auto cam = dynamic_cast<Ogre::Camera*>(object))
				{
					std::cout << " " << cam->getOrientation() * convert(PURGE::CoordinateSystem::get().getForwardVector());
				}
				std::cout << std::endl;
			}
			auto n = node->getChildIterator();
			while (n.hasMoreElements())
			{
				printHelper(dynamic_cast<Ogre::SceneNode*>(n.getNext()), indent + 1);
			}
		}

	}

}

