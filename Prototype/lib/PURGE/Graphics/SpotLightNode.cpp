#include "SpotLightNode.h"
#include "SpotLightDefinition.h"

namespace PURGE
{

	Light*
	SpotLightNode::toggle()
	{
		definition->toggle();
		return this;
	}

	bool
	SpotLightNode::isEnabled() const
	{
		return definition->isEnabled();
	}

	Color
	SpotLightNode::getColor() const
	{
		return definition->getColor();
	}

	Light*
	SpotLightNode::setColor(Color color)
	{
		definition->setColor(color);
		return this;
	}

	SpotLightNode*
	SpotLightNode::setHalfAngle(Angle angle)
	{
		SpotLight::setHalfAngle(angle);
		return this;
	}

	SpotLightNode*
	SpotLightNode::setFullAngle(Angle angle)
	{
		definition->setFullAngle(angle);
		return this;
	}

	Angle
	SpotLightNode::getFullAngle() const
	{
		return definition->getFullAngle();
	}

	SpotLight*
	SpotLightNode::setRange(Real range)
	{
		definition->setRange(range);
		return this;
	}

	Real
	SpotLightNode::getRange() const
	{
		return definition->getRange();
	}

}

