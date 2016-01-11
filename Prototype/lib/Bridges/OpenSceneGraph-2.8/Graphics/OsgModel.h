#ifndef OSGBRIDGE_MODEL_H
#define OSGBRIDGE_MODEL_H 1

#include <PURGE/bridge_include.h>
#include "classes.h"
#include <osg/Node>
#include <osg/NodeVisitor>
#include <osg/PositionAttitudeTransform>
#include <osg/BoundingBox>

namespace PURGEBridge
{

	class OsgModel : public PURGE::ModelTranscript, public PURGE::TickListener
	{

		public:
			OsgModel(OsgGraphics* bridge, PURGE::Model* model);

			void tick(int time);
			void setScale(const PURGE::Vector3& v);
			PURGE::Vector3 getDimensions() const;

		protected:
			osg::PositionAttitudeTransform* positionTransform;
			osg::MatrixTransform* scaleTransform;
			osg::Node* node;

		private:
			OsgGraphics* bridge;
			PURGE::Vector3 boundMin;
			PURGE::Vector3 boundMax;

	};

}

#endif /* OSGBRIDGE_MODEL_H */

