#include "Model.h"

namespace PURGE
{

	ModelNode*
	Model::load(std::string name)
	{
		ModelDefinition* definition(ModelDefinition::load(name));
		return ModelNode::create(definition);
	}

}

