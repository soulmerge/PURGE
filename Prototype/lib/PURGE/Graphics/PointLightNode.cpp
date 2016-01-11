#include "PointLightNode.h"
#include "PointLightDefinition.h"

namespace PURGE
{

	Light*
	PointLightNode::toggle()
	{
		definition->toggle();
		return this;
	}

	bool
	PointLightNode::isEnabled() const
	{
		return definition->isEnabled();
	}

	Color
	PointLightNode::getColor() const
	{
		return definition->getColor();
	}

	Light*
	PointLightNode::setColor(Color color)
	{
		definition->setColor(color);
		return this;
	}

	PointLight*
	PointLightNode::setRange(Real range)
	{
		definition->setRange(range);
		return this;
	}

	Real
	PointLightNode::getRange() const
	{
		return definition->getRange();
	}

}

