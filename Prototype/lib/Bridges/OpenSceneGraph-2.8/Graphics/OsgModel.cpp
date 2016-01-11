#include "OsgModel.h"

#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/Billboard>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/StateAttribute>
#include "OsgGraphics.h"
#include <iostream>

using namespace std;

namespace PURGEBridge
{

	OsgModel::OsgModel(OsgGraphics* bridge, PURGE::Model* model)
	         : ModelTranscript(model)
	         , bridge(bridge)
	{
		node = osgDB::readNodeFile(std::string("resources/Osg/") + model->getName() + ".3ds");
		if (node == NULL)
		{
			//TODO: throw Exception
			exit(19);
		}
		scaleTransform = new osg::MatrixTransform;
		scaleTransform->setMatrix(osg::Matrix::scale(1, 1, 1));
		scaleTransform->setDataVariance(osg::Object::STATIC);
		scaleTransform->addChild(node);
		scaleTransform->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
		positionTransform = new osg::PositionAttitudeTransform();
		positionTransform->addChild(scaleTransform);
		positionTransform->setPosition(osg::Vec3(0, 0, 0));
		bridge->root->addChild(positionTransform);
		loopRegister(-1);
	}

	void
	OsgModel::tick(int time)
	{
		PURGE::Position position(convertedPosition(*OsgGraphics::coordinateSystem));
		PURGE::Point3 location = position.getLocation();
		PURGE::Quaternion quaternion = position.getOrientation();
		positionTransform->setPosition(osg::Vec3(location.x, location.y, location.z));
		positionTransform->setAttitude(osg::Quat(quaternion.x, quaternion.y, quaternion.z, quaternion.w));
		//osg::Vec3 position(getLocation().x, getLocation().y, getLocation().z);
		//positionTransform->setPosition(position);
		//osg::Quat attitude(getOrientation().x, getOrientation().y, getOrientation().z, getOrientation().w);
		//positionTransform->setAttitude(attitude);
	}

	void
	OsgModel::setScale(const PURGE::Vector3& v)
	{
		scaleTransform->setMatrix(osg::Matrix::scale(v.x, v.y, v.z));
	}

	PURGE::Vector3
	OsgModel::getDimensions() const
	{
		return boundMax - boundMin;
	}

}

