#ifndef PURGEBRIDGE_OGRE_1_7_CLASSES_H
#define PURGEBRIDGE_OGRE_1_7_CLASSES_H 1

#include <memory>

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		class OgreRenderer;
		class OgreWindow;
		class OgreSceneNode;
		class OgreModel;
		class OgreCamera;

		typedef std::shared_ptr<OgreRenderer> OgreRendererP;
		typedef std::shared_ptr<OgreWindow> OgreWindowP;
		typedef std::shared_ptr<OgreSceneNode> OgreSceneNodeP;
		typedef std::shared_ptr<OgreModel> OgreModelP;
		typedef std::shared_ptr<OgreCamera> OgreCameraP;
		typedef std::shared_ptr<const OgreRenderer> OgreRendererPC;
		typedef std::shared_ptr<const OgreWindow> OgreWindowPC;
		typedef std::shared_ptr<const OgreSceneNode> OgreSceneNodePC;
		typedef std::shared_ptr<const OgreModel> OgreModelPC;
		typedef std::shared_ptr<const OgreCamera> OgreCameraPC;

		template<class Original, class Transcript> class Transcription;

	}

}

#endif /* PURGEBRIDGE_OGRE_1_7_CLASSES_H */

