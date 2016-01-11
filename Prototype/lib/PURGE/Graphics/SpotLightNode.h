#ifndef PURGE_SPOTLIGHTNODE_H
#define PURGE_SPOTLIGHTNODE_H 1

#include "SpotLight.h"
#include "../Space/FluentSceneNode.h"
#include "../TrackedObject.h"

namespace PURGE
{

	class SpotLightNode : public virtual FluentSceneNode<SpotLightNode>, public virtual SpotLight
	{

		public:
			static SpotLightNode* create(SpotLightDefinition* definition);

			Light* toggle();
			bool isEnabled() const;

			Color getColor() const;
			Light* setColor(Color color);

			SpotLightNode* setHalfAngle(Angle a);
			SpotLightNode* setFullAngle(Angle a);
			Angle getFullAngle() const;

			SpotLightDefinition* getDefinition() const;

			SpotLight* setRange(Real max);
			Real getRange() const;

		private:
			SpotLightNode(SpotLightDefinition* definition);

			SpotLightDefinition* definition;

	};

	inline SpotLightNode*
	SpotLightNode::create(SpotLightDefinition* definition)
	{
		return new SpotLightNode(definition);
	}

	inline
	SpotLightNode::SpotLightNode(SpotLightDefinition* definition)
	             : definition(definition)
	{}

	inline SpotLightDefinition*
	SpotLightNode::getDefinition() const
	{
		return definition;
	}

}

#endif /* PURGE_SPOTLIGHTNODE_H */

