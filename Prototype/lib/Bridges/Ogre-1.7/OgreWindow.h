#ifndef PURGEBRIDGE_OGRE_1_7_OGREWINDOW_H
#define PURGEBRIDGE_OGRE_1_7_OGREWINDOW_H 1

#include <OGRE/Ogre.h>
#include <PURGE/include.h>
#include "classes.h"
#include "Transcription.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		class OgreWindow : public virtual Transcription<PURGE::Window, OgreWindow>
		{

			friend class Transcription<PURGE::Window, OgreWindow>;

			public:

				class OgreViewport : public virtual Transcription<PURGE::Window::Viewport, OgreViewport>
				{

					friend class Transcription<PURGE::Window::Viewport, OgreViewport>;

					protected:
						OgreViewport(PURGE::Window::Viewport* viewport);

						virtual void update(int change);
						virtual void destroy();

					private:
						Ogre::Viewport* viewport;

				};

				Ogre::RenderWindow* getOgreWindow() const;

			protected:
				OgreWindow(PURGE::Window* window);

				void update(int change);
				void destroy();

			private:
				Ogre::RenderWindow* ogreWindow;

		};

		inline Ogre::RenderWindow*
		OgreWindow::getOgreWindow() const
		{
			return ogreWindow;
		}

	}

}

#endif /* PURGEBRIDGE_OGRE_1_7_OGREWINDOW_H */

