#include "Camera.h"
#include "CameraNode.h"

namespace PURGE
{

	CameraNode*
	Camera::create()
	{
		return CameraNode::create(CameraDefinition::create());
	}

}

