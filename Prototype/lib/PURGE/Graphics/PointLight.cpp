#include "PointLight.h"
#include "PointLightNode.h"
#include "PointLightDefinition.h"

namespace PURGE
{

	inline PointLight*
	PointLight::create()
	{
		return PointLightNode::create(PointLightDefinition::create());
	}

}

