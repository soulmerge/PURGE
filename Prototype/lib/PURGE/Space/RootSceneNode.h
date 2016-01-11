#include "SceneNode.h"

#ifndef PURGE_ROOTSCENENODE_H
#define PURGE_ROOTSCENENODE_H 1

namespace PURGE
{

	class RootSceneNode : public SceneNode
	{

		public:
			static RootSceneNode* get();

			virtual ~RootSceneNode();

		private:
			RootSceneNode();

			static RootSceneNode* instance;

	};

	inline
	RootSceneNode::~RootSceneNode()
	{}

	inline
	RootSceneNode::RootSceneNode()
	             : SceneNode(NULL)
	{}

	inline RootSceneNode*
	RootSceneNode::get()
	{
		return instance;
	}

}

#endif /* PURGE_ROOTSCENENODE_H */

