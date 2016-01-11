#ifndef PURGEBRIDGE_OGRE_1_7_OGRESPOTLIGHT_H
#define PURGEBRIDGE_OGRE_1_7_OGRESPOTLIGHT_H 1

#include <OGRE/Ogre.h>
#include <PURGE/include.h>
#include "classes.h"
#include "Transcription.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		class OgreSpotLight : public virtual Transcription<PURGE::SpotLightDefinition, OgreSpotLight>
		{

			friend class Transcription<PURGE::SpotLightDefinition, OgreSpotLight>;

			public:
				Ogre::Light* getOgreLight() const;

			protected:
				OgreSpotLight(PURGE::SpotLightDefinition* original);

				virtual void update(int change);
				virtual void destroy();

			private:
				Ogre::Light* ogreLight;

		};

		inline Ogre::Light*
		OgreSpotLight::getOgreLight() const
		{
			return ogreLight;
		}

	}

}

#endif /* PURGEBRIDGE_OGRE_1_7_OGRESPOTLIGHT_H */

