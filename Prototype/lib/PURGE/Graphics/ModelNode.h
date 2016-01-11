#ifndef PURGE_MODELNODE_H
#define PURGE_MODELNODE_H 1

#include "../classes.h"
#include "../Space/FluentSceneNode.h"
#include "Model.h"
#include "../TrackedObject.h"
#include "ModelDefinition.h"

namespace PURGE
{

	class ModelNode : public virtual FluentSceneNode<ModelNode>, public virtual Model
	{

		public:
			static ModelNode* create(ModelDefinition* definition);

			virtual std::string getName() const;

			ModelDefinition* getDefinition() const;

		private:
			ModelNode(ModelDefinition* definition);

			ModelDefinition* definition;

	};

	inline ModelNode*
	ModelNode::create(ModelDefinition* definition)
	{
		return new ModelNode(definition);
	}

	inline
	ModelNode::ModelNode(ModelDefinition* definition)
	         : definition(definition)
	{}

	inline ModelDefinition*
	ModelNode::getDefinition() const
	{
		return definition;
	}

}

#endif /* PURGE_MODELNODE_H */

