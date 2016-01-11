#ifndef PURGEBRIDGE_OGRE_1_7_OGREMODEL_H
#define PURGEBRIDGE_OGRE_1_7_OGREMODEL_H 1

#include <OGRE/Ogre.h>
#include <PURGE/include.h>
#include "classes.h"
#include "Transcription.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		class OgreModel : public virtual Transcription<PURGE::ModelDefinition, OgreModel>
		{

			friend class Transcription<PURGE::ModelDefinition, OgreModel>;

			public:
				void attachTo(Ogre::SceneNode* node) const;

			protected:
				OgreModel(PURGE::ModelDefinition* original);

				virtual void update(int change);
				virtual void destroy();

		};

		inline
		OgreModel::OgreModel(PURGE::ModelDefinition* original)
		         : Transcription<PURGE::ModelDefinition, OgreModel>(original)
		{}

	}
}

#endif /* PURGEBRIDGE_OGRE_1_7_OGREMODEL_H */

