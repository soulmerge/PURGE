#include "SpotLight.h"
#include "SpotLightNode.h"
#include "SpotLightDefinition.h"

namespace PURGE
{

	SpotLightNode*
	SpotLight::create()
	{
		return SpotLightNode::create(SpotLightDefinition::create());
	}

}

