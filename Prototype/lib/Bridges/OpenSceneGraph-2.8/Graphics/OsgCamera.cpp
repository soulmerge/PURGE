#include "OsgCamera.h"

#include "classes.h"
#include <iostream>
#include <osgGA/TrackballManipulator>
#include <osg/DisplaySettings>

namespace PURGEBridge
{

	void
	OsgCamera::tick(int time)
	{
		if (osgCamera != NULL)
		{
			PURGE::Position position(convertedPosition(*OsgGraphics::coordinateSystem));
			PURGE::Point3 location = position.getLocation();
			PURGE::Point3 lookAt = position.getLocation() + position.getForward();
			PURGE::Point3 up = position.getUp();
			//std::cout << location << std::endl;
			//std::cout << lookAt << std::endl;
			//std::cout << up << std::endl;
			//std::cout << std::endl;
			osg::Vec3 osglocation(location.x, location.y, location.z);
			osg::Vec3 osglookAt(lookAt.x, lookAt.y, lookAt.z);
			osg::Vec3 osgup(up.x, up.y, up.z);
			osgCamera->setViewMatrixAsLookAt(osglocation, osglookAt, osgup);
		}
	}

	void
	OsgCamera::setCamera(osg::Camera* camera)
	{
		osgCamera = camera;
		GLenum buffer = GL_BACK;
		osgCamera->setDrawBuffer(buffer);
		osgCamera->setReadBuffer(buffer);
		//osgCamera->setClearColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
		osgCamera->setClearColor(osg::Vec4(0.0, 0.0, 0.0, 1.0));
	}

}

