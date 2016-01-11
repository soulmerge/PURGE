#ifndef OSGVIEWPORT_H
#define OSGVIEWPORT_H 1

#include <PURGE/bridge_include.h>
#include "classes.h"
#include <osg/Viewport>
#include <osg/ref_ptr>
#include <osg/GraphicsContext>
#include <osgViewer/View>

namespace PURGEBridge
{

	class OsgViewport : public PURGE::ViewportTranscript
	{

		public:
			OsgViewport(OsgGraphics* bridge, PURGE::Window* window, PURGE::Viewport* viewport, PURGE::Camera* camera, int zOrder, PURGE::Real left, PURGE::Real top, PURGE::Real width, PURGE::Real height, bool relativeSize);

			void attach(PURGE::Camera* camera);

			osg::Camera* getOsgCamera() const;

		private:
			osg::ref_ptr<osg::Viewport> osgViewport;
			osg::ref_ptr<osgViewer::View> osgView;
			OsgGraphics* bridge;

	};

}

#include "OsgCamera.h"
#include "OsgGraphics.h"

namespace PURGEBridge
{

	inline osg::Camera*
	OsgViewport::getOsgCamera() const
	{
		return osgView->getCamera();
	}

	inline void
	OsgViewport::attach(PURGE::Camera* camera)
	{
		static_cast<OsgCamera*>(camera->getTranscript(bridge))->setCamera(getOsgCamera());
	}

}

#endif /* OSGVIEWPORT_H */

