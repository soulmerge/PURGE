#ifndef PURGEBRIDGE_OGRE_1_7_OGRESCENENODE_H
#define PURGEBRIDGE_OGRE_1_7_OGRESCENENODE_H 1

#include <OGRE/Ogre.h>
#include <PURGE/include.h>
#include "classes.h"
#include "Transcription.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		class OgreSceneNode : public virtual Transcription<PURGE::SceneNode, OgreSceneNode>
		{

			friend class Transcription<PURGE::SceneNode, OgreSceneNode>;

			protected:
				OgreSceneNode(PURGE::SceneNode* original);

				virtual void update(int change);
				virtual void destroy();

			private:
				Ogre::SceneNode* ogreNode;

		};

	}

}

#endif /* PURGEBRIDGE_OGRE_1_7_OGRESCENENODE_H */

