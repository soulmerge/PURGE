#ifndef PURGE_FLUENTSCENENODE_H
#define PURGE_FLUENTSCENENODE_H 1

#include "SceneNode.h"

namespace PURGE
{

	template<class T>
	class FluentSceneNode : public virtual SceneNode
	{

		public:

			T* attachTo(SceneNode* newParent);

			// Location
			T* move(const Vector3& vector);
			T* move(Real x, Real y, Real z);
			T* move(const Vector3& vector, Real amount);
			T* move(Real x, Real y, Real z, Real amount);
			T* move(const Vector3& vector, const SceneNode* context);
			T* move(Real x, Real y, Real z, const SceneNode* context);
			T* moveLeft(Real amount);
			T* moveLeft(Real amount, const SceneNode* context);
			T* moveRight(Real amount);
			T* moveRight(Real amount, const SceneNode* context);
			T* moveUp(Real amount);
			T* moveUp(Real amount, const SceneNode* context);
			T* moveDown(Real amount);
			T* moveDown(Real amount, const SceneNode* context);
			T* moveForward(Real amount);
			T* moveForward(Real amount, const SceneNode* context);
			T* moveBackward(Real amount);
			T* moveBackward(Real amount, const SceneNode* context);

			// Rotation
			T* rotate(Angle angle, Vector3 axis);
			T* rotate(Angle angle, Vector3 axis, const SceneNode* context);
			T* rotateLeft(Angle amount);
			T* rotateLeft(Angle amount, const SceneNode* context);
			T* rotateRight(Angle amount);
			T* rotateRight(Angle amount, const SceneNode* context);
			T* rotateUp(Angle amount);
			T* rotateUp(Angle amount, const SceneNode* context);
			T* rotateDown(Angle amount);
			T* rotateDown(Angle amount, const SceneNode* context);
			T* tiltLeft(Angle amount);
			T* tiltLeft(Angle amount, const SceneNode* context);
			T* tiltRight(Angle amount);
			T* tiltRight(Angle amount, const SceneNode* context);
			T* setDirection(Vector3 direction, bool keepTilt = true);
			T* setDirection(Real x, Real y, Real z, bool keepTilt = true);
			T* lookAt(const SceneNode* target, bool keepTilt = true);

			// Scale
			T* setScale(Real scale);
			T* setScale(Real scale, const SceneNode* context);
			T* scale(Real scalar);

	};

	template<class T> T*
	FluentSceneNode<T>::attachTo(SceneNode* newParent)
	{
		SceneNode::attachTo(newParent);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::move(const Vector3& vector)
	{
		SceneNode::move(vector);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::move(Real x, Real y, Real z)
	{
		SceneNode::move(x, y, z);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::move(const Vector3& vector, Real amount)
	{
		SceneNode::move(vector, amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::move(Real x, Real y, Real z, Real amount)
	{
		SceneNode::move(x, y, z, amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::move(const Vector3& vector, const SceneNode* context)
	{
		SceneNode::move(vector, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::move(Real x, Real y, Real z, const SceneNode* context)
	{
		SceneNode::move(x, y, z, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveLeft(Real amount)
	{
		SceneNode::moveLeft(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveLeft(Real amount, const SceneNode* context)
	{
		SceneNode::moveLeft(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveRight(Real amount)
	{
		SceneNode::moveRight(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveRight(Real amount, const SceneNode* context)
	{
		SceneNode::moveRight(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveUp(Real amount)
	{
		SceneNode::moveUp(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveUp(Real amount, const SceneNode* context)
	{
		SceneNode::moveUp(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveDown(Real amount)
	{
		SceneNode::moveDown(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveDown(Real amount, const SceneNode* context)
	{
		SceneNode::moveDown(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveForward(Real amount)
	{
		SceneNode::moveForward(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveForward(Real amount, const SceneNode* context)
	{
		SceneNode::moveForward(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveBackward(Real amount)
	{
		SceneNode::moveBackward(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::moveBackward(Real amount, const SceneNode* context)
	{
		SceneNode::moveBackward(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotate(Angle angle, Vector3 axis)
	{
		SceneNode::rotate(angle, axis);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotate(Angle angle, Vector3 axis, const SceneNode* context)
	{
		SceneNode::rotate(angle, axis, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotateLeft(Angle amount)
	{
		SceneNode::rotateLeft(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotateLeft(Angle amount, const SceneNode* context)
	{
		SceneNode::rotateLeft(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotateRight(Angle amount)
	{
		SceneNode::rotateRight(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotateRight(Angle amount, const SceneNode* context)
	{
		SceneNode::rotateRight(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotateUp(Angle amount)
	{
		SceneNode::rotateUp(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotateUp(Angle amount, const SceneNode* context)
	{
		SceneNode::rotateUp(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotateDown(Angle amount)
	{
		SceneNode::rotateDown(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::rotateDown(Angle amount, const SceneNode* context)
	{
		SceneNode::rotateDown(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::tiltLeft(Angle amount)
	{
		SceneNode::tiltLeft(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::tiltLeft(Angle amount, const SceneNode* context)
	{
		SceneNode::tiltLeft(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::tiltRight(Angle amount)
	{
		SceneNode::tiltRight(amount);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::tiltRight(Angle amount, const SceneNode* context)
	{
		SceneNode::tiltRight(amount, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::setDirection(Vector3 direction, bool keepTilt)
	{
		SceneNode::setDirection(direction, keepTilt);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::setDirection(Real x, Real y, Real z, bool keepTilt)
	{
		SceneNode::setDirection(x, y, z, keepTilt);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::lookAt(const SceneNode* target, bool keepTilt)
	{
		SceneNode::lookAt(target, keepTilt);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::setScale(Real scale)
	{
		SceneNode::setScale(scale);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::setScale(Real scale, const SceneNode* context)
	{
		SceneNode::setScale(scale, context);
		return dynamic_cast<T*>(this);
	}

	template<class T> T*
	FluentSceneNode<T>::scale(Real scalar)
	{
		SceneNode::scale(scalar);
		return dynamic_cast<T*>(this);
	}

}

#endif /* PURGE_FLUENTSCENENODE_H */

