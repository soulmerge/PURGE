#include "OsgGraphics.h"

#include <iostream>
#include <osgGA/TrackballManipulator>
#include <osg/LightModel>
#include <SDL/SDL.h>

namespace PURGEBridge
{

	const PURGE::CoordinateSystem*
	OsgGraphics::coordinateSystem;

	void
	OsgGraphics::_init()
	{
		if (!SDL_WasInit(SDL_INIT_VIDEO)) {
			SDL_Init(SDL_INIT_VIDEO);
		}
		root = new osg::Group();
		osg::LightModel* model = new osg::LightModel();
		model->setAmbientIntensity(osg::Vec4(1, 1, 1, 1));
		osg::StateSet* set = root->getOrCreateStateSet();
		set->setAttribute(model);
		viewer = new osgViewer::CompositeViewer();
		coordinateSystem = &PURGE::CoordinateSystem::PX_NY_PZ;
		//std::vector<const FileFormat*>* formats(const_cast<std::vector<const FileFormat*>* >(&fileformats));
		//formats->push_back(&FileFormat::OSG);
		//formats->push_back(&FileFormat::STUDIO_MAX);
		//formats->push_back(&FileFormat::JPEG);
		//formats->push_back(&FileFormat::TGA);
	}

	const PURGE::GraphicsEngine*
	OsgGraphics::getScreenDimensions(int* width, int* height) const
	{
		const SDL_VideoInfo* videoInfo;
		videoInfo = SDL_GetVideoInfo();
		if (width != NULL)
		{
			*width = videoInfo->current_w;
		}
		if (height != NULL)
		{
			*height = videoInfo->current_h;
		}
		return this;
	}

	PURGE::GraphicsEngine*
	OsgGraphics::getScreenDimensions(int* width, int* height)
	{
		const SDL_VideoInfo* videoInfo;
		videoInfo = SDL_GetVideoInfo();
		if (width != NULL)
		{
			*width = videoInfo->current_w;
		}
		if (height != NULL)
		{
			*height = videoInfo->current_h;
		}
		return this;
	}

}

