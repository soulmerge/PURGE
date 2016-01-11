#ifndef PURGE_POINTLIGHTNODE_H
#define PURGE_POINTLIGHTNODE_H 1

#include "PointLight.h"
#include "../Space/FluentSceneNode.h"
#include "../TrackedObject.h"

namespace PURGE
{

	class PointLightNode : public virtual PointLight, public virtual FluentSceneNode<PointLightNode>
	{

		public:
			static PointLightNode* create(PointLightDefinition* definition);

			Light* toggle();
			bool isEnabled() const;

			Color getColor() const;
			Light* setColor(Color color);

			PointLightDefinition* getDefinition() const;

			PointLight* setRange(Real max);
			Real getRange() const;

		private:
			PointLightNode(PointLightDefinition* definition);

			PointLightDefinition* definition;

	};

	inline PointLightNode*
	PointLightNode::create(PointLightDefinition* definition)
	{
		return new PointLightNode(definition);
	}

	inline
	PointLightNode::PointLightNode(PointLightDefinition* definition)
	              : definition(definition)
	{}

	inline PointLightDefinition*
	PointLightNode::getDefinition() const
	{
		return definition;
	}

}

#endif /* PURGE_POINTLIGHTNODE_H */

