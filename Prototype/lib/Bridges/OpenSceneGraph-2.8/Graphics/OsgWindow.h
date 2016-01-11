#ifndef OSGWINDOW_H
#define OSGWINDOW_H 1

#include <PURGE/bridge_include.h>

#include "classes.h"
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/View>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>

namespace PURGEBridge
{

	class OsgScreen;

	class OsgWindow : public PURGE::WindowTranscript, public osgGA::GUIEventHandler
	{

		public:
			OsgWindow(OsgGraphics* bridge, PURGE::Window* window);

			bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter&);
			OsgWindow* addEventHandler(osg::ref_ptr<osgViewer::View> view);

			osg::ref_ptr<osgViewer::GraphicsWindow> getGraphicsContext() const;

			PURGE::ViewportTranscript* createViewportTranscript(PURGE::Viewport* viewport, PURGE::Camera* camera, int zOrder, PURGE::Real top, PURGE::Real left, PURGE::Real width, PURGE::Real height, bool relativeSize);
			void getDimensions(int* width, int* height) const;

		private:
			PURGE::Key oisToPurge(const osgGA::GUIEventAdapter& ea) const;

			int lastX;
			int lastY;
			OsgGraphics* bridge;

			osg::ref_ptr<osg::GraphicsContext::Traits> traits;
			osg::ref_ptr<osgViewer::GraphicsWindow> graphicsContext;
			osg::ref_ptr<osgViewer::View> view;
			bool pressedKeys[256];

			static int systemIndex;

	};

}

#include "OsgViewport.h"

namespace PURGEBridge
{

	inline osg::ref_ptr<osgViewer::GraphicsWindow>
	OsgWindow::getGraphicsContext() const
	{
		return graphicsContext;
	}

	inline PURGE::ViewportTranscript*
	OsgWindow::createViewportTranscript(PURGE::Viewport* viewport, PURGE::Camera* camera, int zOrder, PURGE::Real top, PURGE::Real left, PURGE::Real width, PURGE::Real height, bool relativeSize)
	{
		return new OsgViewport(bridge, viewport->getWindow(), viewport, camera, zOrder, top, left, width, height, relativeSize);
	}

	inline void
	OsgWindow::getDimensions(int* width, int* height) const
	{
		int _x, _y, _width, _height;
		graphicsContext->getWindowRectangle(_x, _y, _width, _height);
		if (width)
		{
			*width = _width;
		}
		if (height)
		{
			*height = _height;
		}
	}

}

#endif /* OSGWINDOW_H */

