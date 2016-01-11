#include "OsgViewport.h"

#include "OsgCamera.h"
#include "OsgWindow.h"
#include <iostream>
#include "OsgGraphics.h"

namespace PURGEBridge
{

	OsgViewport::OsgViewport(OsgGraphics* bridge, PURGE::Window* window, PURGE::Viewport* viewport, PURGE::Camera* camera, int zOrder, PURGE::Real left, PURGE::Real top, PURGE::Real width, PURGE::Real height, bool relativeSize)
	           : PURGE::ViewportTranscript(viewport)
	           , bridge(bridge)
	{
		osgViewport = new osg::Viewport(window->getWidth() * left, window->getHeight() * (1.0 - (top + height)), window->getWidth() * width, window->getHeight() * height);
		//osgViewport = new osg::Viewport(window->getWidth() * left, window->getHeight() * (1.0 - top), window->getWidth() * width, window->getHeight() * height);
		osgView = new osgViewer::View;
		osgView->getCamera()->setGraphicsContext(static_cast<OsgWindow*>(window->getTranscript(bridge))->getGraphicsContext().get());
		osgView->getCamera()->setViewport(osgViewport.get());
		osgView->getCamera()->setProjectionMatrixAsPerspective(50, viewport->getWidth() / viewport->getHeight(), 5, 10000);
		osgView->setSceneData(bridge->root);
		static_cast<OsgWindow*>(window->getTranscript(bridge))->addEventHandler(osgView); 
		bridge->viewer->addView(osgView.get());
		if (camera)
		{
			static_cast<OsgCamera*>(camera->getTranscript(bridge))->setCamera(getOsgCamera());
		}
		osgView->setLightingMode(osg::View::HEADLIGHT);
		osg::Light* light = new osg::Light();
		light->setAmbient(osg::Vec4d(0.0f, 0.0f, 0.0f, 0.0f));
		light->setDiffuse(osg::Vec4d(0.0f, 0.0f, 0.0f, 0.0f));
		light->setSpecular(osg::Vec4d(0.0f, 0.0f, 0.0f, 0.0f));
		//light->setLightNum(0);
		//light->setSpotExponent(0.1);
		osgView->setLight(light);
	}

}

