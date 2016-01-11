#ifndef PURGEBRIDGE_OSG
#define PURGEBRIDGE_OSG 1

#include <PURGE/bridge_include.h>

// #include <osg/Node>
#include <osg/Group>
#include <osgViewer/CompositeViewer>

namespace PURGEBridge
{

	class OsgGraphics : public PURGE::GraphicsEngine
	{

		public:
			static const PURGE::CoordinateSystem* coordinateSystem;

		public:
			OsgGraphics();

			GraphicsEngine* getScreenDimensions(int* width, int* height);
			const GraphicsEngine* getScreenDimensions(int* width, int* height) const;

			osg::Group* root;
			osgViewer::CompositeViewer* viewer;

		protected:
			void _init();
			void _shutdown();
			void _tick();

			PURGE::ModelTranscript* createModelTranscript(PURGE::Model* model);
			PURGE::CameraTranscript* createCameraTranscript(PURGE::Camera* camera);
			PURGE::WindowTranscript* createWindowTranscript(PURGE::Window* window);

	};

}

#include "OsgModel.h"
#include "OsgCamera.h"
#include "OsgWindow.h"

namespace PURGEBridge
{

	inline
	OsgGraphics::OsgGraphics()
	{
		_init();
	}

	inline PURGE::ModelTranscript*
	OsgGraphics::createModelTranscript(PURGE::Model* model)
	{
		return new OsgModel(this, model);
	}

	inline PURGE::CameraTranscript*
	OsgGraphics::createCameraTranscript(PURGE::Camera* camera)
	{
		return new OsgCamera(this, camera);
	}

	inline PURGE::WindowTranscript*
	OsgGraphics::createWindowTranscript(PURGE::Window* window)
	{
		return new OsgWindow(this, window);
	}

	inline void
	OsgGraphics::_shutdown()
	{}

	inline void
	OsgGraphics::_tick()
	{
		viewer->frame();
	}

}

#endif /* PURGEBRIDGE_OSG */

