#ifndef OSG_CAMERA_H
#define OSG_CAMERA_H 1

#include <PURGE/bridge_include.h>
#include "classes.h"
#include <osgViewer/Viewer>
#include <osg/ref_ptr>

namespace PURGEBridge
{

	class OsgViewport;

	class OsgCamera : public PURGE::CameraTranscript, public PURGE::TickListener
	{

		public:
			OsgCamera(OsgGraphics* bridge, PURGE::Camera* purgeCamera);

			OsgCamera* setSkybox(std::string descriptor) {assert(false); /* TODO: not implemented */}
			void tick(int time);
			void setCamera(osg::Camera* osgCam);

		private:
			OsgGraphics* bridge;
			osg::ref_ptr<osg::Camera> osgCamera;

	};

}

#include "OsgViewport.h"

namespace PURGEBridge
{

	inline
	OsgCamera::OsgCamera(OsgGraphics* bridge, PURGE:: Camera* purgeCamera)
	         : CameraTranscript(purgeCamera)
	         , bridge(bridge)
	         , osgCamera(NULL)
	{
		loopRegister(-1);
	}

}

#endif /* OSG_CAMERA_H */

