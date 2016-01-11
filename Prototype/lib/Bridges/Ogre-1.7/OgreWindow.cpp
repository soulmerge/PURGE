#include "OgreWindow.h"

#include "OgreRenderer.h"
#include "OgreCamera.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		OgreWindow::OgreWindow(PURGE::Window* window)
		          : Transcription<PURGE::Window, OgreWindow>(window)
		{
			ogreWindow = OgreRenderer::getInstance()->getOgreRoot()->createRenderWindow("Ogre RenderWindow", window->getWidth(), window->getHeight(), false);
		}

		void
		OgreWindow::update(int change)
		{
			throw std::string("OgreWindow: unidentified change #") + boost::lexical_cast<std::string>(change);
		}

		void
		OgreWindow::destroy()
		{
			ogreWindow->destroy();
		}

		OgreWindow::OgreViewport::OgreViewport(PURGE::Window::Viewport* viewport)
		                        : Transcription<PURGE::Window::Viewport, OgreViewport>(viewport)
		{
			OgreWindow* ogreWindow(OgreWindow::getTranscript(viewport->getWindow()));
			OgreCamera* ogreCamera(OgreCamera::getTranscript(viewport->getCamera()->getDefinition()));
			ogreWindow->ogreWindow->addViewport(ogreCamera->getOgreCamera(), 0, 0, 0, viewport->getWidth(), viewport->getHeight());
		}

		void
		OgreWindow::OgreViewport::update(int change)
		{
			throw std::string("OgreWindow::OgreViewport: unidentified change #") + boost::lexical_cast<std::string>(change);
		}

		void
		OgreWindow::OgreViewport::destroy()
		{
			// TODO: implement
		}

	}

}

