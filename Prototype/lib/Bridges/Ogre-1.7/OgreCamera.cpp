#include "OgreCamera.h"

#include "OgreRenderer.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		OgreCamera::OgreCamera(PURGE::CameraDefinition* camera)
		          : Transcription<PURGE::CameraDefinition, OgreCamera>(camera)
		{
			ogreCamera = OgreRenderer::getInstance()->getOgreSceneManager()->createCamera(OgreRenderer::getInstance()->createUniqueString("Camera"));
			ogreCamera->setPosition(0, 0, 0);
			ogreCamera->lookAt(OgreRenderer::convert(PURGE::CoordinateSystem::get().getForwardVector()));
            ogreCamera->setAutoAspectRatio(true);
			update(PURGE::CameraDefinition::CHANGE_VISIBLERANGE);
		}

		void
		OgreCamera::update(int change)
		{
			switch (change)
			{
				case PURGE::CameraDefinition::CHANGE_VISIBLERANGE:
					// TODO: Difference in distance should not be larger than 1^16 (or 1^32, depending on hardware)
					// see http://www.ogre3d.org/docs/api/html/classOgre_1_1Frustum.html#a9429acc6a3e8cfd4fbd0b2472c82f565
					ogreCamera->setNearClipDistance(original->getMinVisibleRange());
					ogreCamera->setFarClipDistance(original->getMaxVisibleRange());
					break;
				default:
					throw std::string("OgreSceneNode: unidentified change #") + boost::lexical_cast<std::string>(change);
			}
		}

		void
		OgreCamera::destroy()
		{
			delete ogreCamera;
		}

	}

}

