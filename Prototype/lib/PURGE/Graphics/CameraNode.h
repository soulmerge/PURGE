#ifndef PURGE_CAMERANODE_H
#define PURGE_CAMERANODE_H 1

#include "../classes.h"
#include "../Space/FluentSceneNode.h"
#include "Camera.h"
#include "CameraDefinition.h"

namespace PURGE
{

	class CameraNode : public virtual FluentSceneNode<CameraNode>, public virtual Camera
	{

		public:
			static std::list<CameraNode*> getAllInstances();
			static std::list<CameraNode*> getNewInstances();
			static std::list<CameraNode*> getUpdatedInstances();
			static std::list<CameraNode*> getDestroyedInstances();
			static CameraNode* create(CameraDefinition* definition);

			CameraDefinition* getDefinition() const;

			virtual Camera* setVisibleRange(Real min, Real max);

			virtual Real getMinVisibleRange() const;
			virtual Real getMaxVisibleRange() const;

		private:
			static std::list<CameraNode*> filterInstances(const std::list<SceneNode*>& v);
			CameraNode(CameraDefinition* definition);

			CameraDefinition* definition;

	};

	inline std::list<CameraNode*>
	CameraNode::getAllInstances()
	{
		return filterInstances(TrackedObject<SceneNode>::getAllInstances());
	}

	inline std::list<CameraNode*>
	CameraNode::getNewInstances()
	{
		return filterInstances(TrackedObject<SceneNode>::getNewInstances());
	}

	inline std::list<CameraNode*>
	CameraNode::getUpdatedInstances()
	{
		return filterInstances(TrackedObject<SceneNode>::getUpdatedInstances());
	}

	inline std::list<CameraNode*>
	CameraNode::getDestroyedInstances()
	{
		return filterInstances(TrackedObject<SceneNode>::getDestroyedInstances());
	}

	inline std::list<CameraNode*>
	CameraNode::filterInstances(const std::list<SceneNode*>& in)
	{
		std::list<CameraNode*> out;
		for (auto i = in.begin(); i != in.end(); i++)
		{
			if (CameraNode* x = dynamic_cast<CameraNode*>(*i))
			{
				out.push_back(x);
			}
		}
		return out;
	}

	inline CameraNode*
	CameraNode::create(CameraDefinition* definition)
	{
		return new CameraNode(definition);
	}

	inline
	CameraNode::CameraNode(CameraDefinition* definition)
	         : definition(definition)
	{}

	inline CameraDefinition*
	CameraNode::getDefinition() const
	{
		return definition;
	}

	inline Camera*
	CameraNode::setVisibleRange(Real min, Real max)
	{
		definition->setVisibleRange(min, max);
		return this;
	}

	inline Real
	CameraNode::getMinVisibleRange() const
	{
		return definition->getMinVisibleRange();
	}

	inline Real
	CameraNode::getMaxVisibleRange() const
	{
		return definition->getMaxVisibleRange();
	}

}

#endif /* PURGE_CAMERANODE_H */

