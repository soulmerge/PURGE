#include "OgreSceneNode.h"

#include "OgreRenderer.h"
#include "OgreModel.h"
#include "OgreCamera.h"
#include "OgreSpotLight.h"
#include "OgrePointLight.h"
#include <string>
#include <boost/lexical_cast.hpp>

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		OgreSceneNode::OgreSceneNode(PURGE::SceneNode* sceneNode)
		             : Transcription<PURGE::SceneNode, OgreSceneNode>(sceneNode)
		{
			// create parent
            PURGE::SceneNode* parent(sceneNode->getParentNode());
			if (!parent)
			{
				ogreNode = OgreRenderer::getInstance()->getOgreSceneManager()->getRootSceneNode();
			}
			else
			{
				if (!instances[parent])
				{
					OgreSceneNode::create(parent);
				}
				// create node
				ogreNode = instances[parent]->ogreNode->createChildSceneNode();
				// handle attached model
				PURGE::ModelNode* m(dynamic_cast<PURGE::ModelNode*>(sceneNode));
				if (m)
				{
					OgreModel::getTranscript(m->getDefinition())->attachTo(ogreNode);
				}
				// handle attached camera
				PURGE::CameraNode* c(dynamic_cast<PURGE::CameraNode*>(sceneNode));
				if (c)
				{
					ogreNode->attachObject(OgreCamera::getTranscript(c->getDefinition())->getOgreCamera());
				}
				// handle attached spot light
				PURGE::SpotLightNode* s(dynamic_cast<PURGE::SpotLightNode*>(sceneNode));
				if (s)
				{
					ogreNode->attachObject(OgreSpotLight::getTranscript(s->getDefinition())->getOgreLight());
				}
				// handle attached point light
				PURGE::PointLightNode* p(dynamic_cast<PURGE::PointLightNode*>(sceneNode));
				if (p)
				{
					ogreNode->attachObject(OgrePointLight::getTranscript(p->getDefinition())->getOgreLight());
				}
				// set initial properties
				update(PURGE::SceneNode::CHANGE_LOCATION);
				update(PURGE::SceneNode::CHANGE_ROTATION);
				update(PURGE::SceneNode::CHANGE_SCALE);
			}
		}

		void
		OgreSceneNode::update(int change)
		{
			if (change == PURGE::SceneNode::CHANGE_LOCATION)
			{
				ogreNode->setPosition(OgreRenderer::convert(original->getLocation()));
			}
			else if (change == PURGE::SceneNode::CHANGE_ROTATION)
			{
				ogreNode->setOrientation(OgreRenderer::convert(original->getRotation()));
			}
			else if (change == PURGE::SceneNode::CHANGE_SCALE)
			{
				PURGE::Real scale = original->getScale();
				ogreNode->setScale(scale, scale, scale);
			}
			else if (change == PURGE::SceneNode::CHANGE_PARENT)
			{
				PURGE::SceneNode* parent(original->getParentNode());
				if (!instances[parent])
				{
					OgreSceneNode::create(parent);
				}
				ogreNode->getParentSceneNode()->removeChild(ogreNode);
				instances[parent]->ogreNode->addChild(ogreNode);
			}
			else
			{
				throw std::string("OgreSceneNode: unidentified change #") + boost::lexical_cast<std::string>(change);
			}
		}

		void
		OgreSceneNode::destroy()
		{
			ogreNode->removeAndDestroyAllChildren();
            Ogre::SceneNode* parent(ogreNode->getParentSceneNode());
            if (parent)
            {
                parent->removeChild(ogreNode);
            }
            delete ogreNode;
		}

	}

}

