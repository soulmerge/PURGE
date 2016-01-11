#include "ModelNode.h"

namespace PURGE
{

	std::string
	ModelNode::getName() const
	{
		return definition->getName();
	}

}

