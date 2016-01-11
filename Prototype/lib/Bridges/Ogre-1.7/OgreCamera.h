#ifndef PURGEBRIDGE_OGRE_1_7_OGRECAMERA_H
#define PURGEBRIDGE_OGRE_1_7_OGRECAMERA_H 1

#include <OGRE/Ogre.h>
#include <PURGE/include.h>
#include "classes.h"
#include "Transcription.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		class OgreCamera : public virtual Transcription<PURGE::CameraDefinition, OgreCamera>
		{

			friend class Transcription<PURGE::CameraDefinition, OgreCamera>;

			public:
				Ogre::Camera* getOgreCamera() const;

			protected:
				void update(int change);
				void destroy();

				OgreCamera(PURGE::CameraDefinition* camera);

			private:
				Ogre::Camera* ogreCamera;

		};

		inline Ogre::Camera*
		OgreCamera::getOgreCamera() const
		{
			return ogreCamera;
		}

	}

}

#endif /* PURGEBRIDGE_OGRE_1_7_OGRECAMERA_H */

