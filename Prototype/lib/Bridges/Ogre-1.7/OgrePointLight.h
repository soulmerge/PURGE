#ifndef PURGEBRIDGE_OGRE_1_7_OGREPOINTLIGHT_H
#define PURGEBRIDGE_OGRE_1_7_OGREPOINTLIGHT_H 1

#include <OGRE/Ogre.h>
#include <PURGE/include.h>
#include "classes.h"
#include "Transcription.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		class OgrePointLight : public virtual Transcription<PURGE::PointLightDefinition, OgrePointLight>
		{

			friend class Transcription<PURGE::PointLightDefinition, OgrePointLight>;

			public:
				Ogre::Light* getOgreLight() const;

			protected:
				OgrePointLight(PURGE::PointLightDefinition* original);

				virtual void update(int change);
				virtual void destroy();

			private:
				Ogre::Light* ogreLight;

		};

		inline Ogre::Light*
		OgrePointLight::getOgreLight() const
		{
			return ogreLight;
		}

	}

}

#endif /* PURGEBRIDGE_OGRE_1_7_OGREPOINTLIGHT_H */

