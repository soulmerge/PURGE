#ifndef PURGE_SCENENODE_H
#define PURGE_SCENENODE_H 1

#include "../classes.h"
#include "../TrackedObject.h"
#include "../Math/Angle.h"
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"
#include "CoordinateSystem.h"

namespace PURGE
{

	class SceneNode : public virtual TrackedObject<SceneNode>
	{

		public:
			static const int CHANGE_LOCATION = 0x01;
			static const int CHANGE_ROTATION = 0x02;
			static const int CHANGE_SCALE    = 0x04;
			static const int CHANGE_PARENT   = 0x08;

			static SceneNode* root();
			static SceneNode* create();
			static SceneNode* create(SceneNode* parent);

			virtual ~SceneNode();

			SceneNode* attachTo(SceneNode* newParent);
			SceneNode* getParentNode() const;

			// Location
			SceneNode* move(const Vector3& vector);
			SceneNode* move(Real x, Real y, Real z);
			SceneNode* move(const Vector3& vector, Real amount);
			SceneNode* move(Real x, Real y, Real z, Real amount);
			SceneNode* move(const Vector3& vector, const SceneNode* context);
			SceneNode* move(Real x, Real y, Real z, const SceneNode* context);
			SceneNode* moveLeft(Real amount);
			SceneNode* moveLeft(Real amount, const SceneNode* context);
			SceneNode* moveRight(Real amount);
			SceneNode* moveRight(Real amount, const SceneNode* context);
			SceneNode* moveUp(Real amount);
			SceneNode* moveUp(Real amount, const SceneNode* context);
			SceneNode* moveDown(Real amount);
			SceneNode* moveDown(Real amount, const SceneNode* context);
			SceneNode* moveForward(Real amount);
			SceneNode* moveForward(Real amount, const SceneNode* context);
			SceneNode* moveBackward(Real amount);
			SceneNode* moveBackward(Real amount, const SceneNode* context);

			Vector3 vectorTo(const SceneNode* destination) const;
			Vector3 vectorTo(const Vector3& destination) const;
			Vector3 vectorTo(Real x, Real y, Real z) const;
			Vector3 getLocation() const;
			Vector3 getLocation(const SceneNode* context) const;

			// Rotation
			SceneNode* setRotation(const Quaternion& q);
			SceneNode* setRotation(const Quaternion& q, const SceneNode* context);
			SceneNode* setRotation(Angle angle, Vector3 axis);
			SceneNode* setRotation(Angle angle, Vector3 axis, const SceneNode* context);
			SceneNode* rotate(const Quaternion& q);
			SceneNode* rotate(const Quaternion& q, const SceneNode* context);
			SceneNode* rotate(Angle angle, Vector3 axis);
			SceneNode* rotate(Angle angle, Vector3 axis, const SceneNode* context);
			SceneNode* rotateLeft(Angle amount);
			SceneNode* rotateLeft(Angle amount, const SceneNode* context);
			SceneNode* rotateRight(Angle amount);
			SceneNode* rotateRight(Angle amount, const SceneNode* context);
			SceneNode* rotateUp(Angle amount);
			SceneNode* rotateUp(Angle amount, const SceneNode* context);
			SceneNode* rotateDown(Angle amount);
			SceneNode* rotateDown(Angle amount, const SceneNode* context);
			SceneNode* tiltLeft(Angle amount);
			SceneNode* tiltLeft(Angle amount, const SceneNode* context);
			SceneNode* tiltRight(Angle amount);
			SceneNode* tiltRight(Angle amount, const SceneNode* context);
			SceneNode* setDirection(const Vector3& direction, bool keepTilt = true);
			SceneNode* setDirection(Real x, Real y, Real z, bool keepTilt = true);
			SceneNode* lookAt(const SceneNode* target, bool keepTilt = true);
			SceneNode* lookAt(const Vector3& position, bool keepTilt = true);
			SceneNode* lookAt(Real x, Real y, Real z, bool keepTilt = true);

			Vector3 getLeftVector() const;
			Vector3 getRightVector() const;
			Vector3 getUpVector() const;
			Vector3 getDownVector() const;
			Vector3 getForwardVector() const;
			Vector3 getBackwardVector() const;
			Quaternion getRotation() const;
			Quaternion getRotation(const SceneNode* context) const;

			// Scale
			SceneNode* setScale(Real scale);
			SceneNode* setScale(Real scale, const SceneNode* context);
			SceneNode* scale(Real scalar);

			Real getScale() const;
			Real getScale(const SceneNode* context) const;

		protected:
			SceneNode();
			SceneNode(SceneNode* parent);

			static SceneNode* _root;

			SceneNode* parent;
			Vector3 location;
			Quaternion orientation;
			Real _scale;

	};

}

#include "RootSceneNode.h"

namespace PURGE
{

	inline SceneNode*
	SceneNode::create()
	{
		return new SceneNode();
	}

	inline SceneNode*
	SceneNode::create(SceneNode* parent)
	{
		return new SceneNode(parent);
	}

	inline
	SceneNode::SceneNode()
	         : parent(root())
	         , _scale(1)
	{
		init();
	}

	inline
	SceneNode::SceneNode(SceneNode* parent)
	         : parent(parent)
	         , _scale(1)
	{
		init();
	}

	inline
	SceneNode::~SceneNode()
	{}

	inline SceneNode*
	SceneNode::root()
	{
		if (!_root) {
			_root = new SceneNode(NULL);
		}
		return _root;
	}

	inline SceneNode*
	SceneNode::attachTo(SceneNode* newParent)
	{
		// TODO: check circular dependency
		parent = newParent;
		markChanged(CHANGE_PARENT);
		return this;
	}

	inline SceneNode*
	SceneNode::getParentNode() const
	{
		return parent;
	}

	inline SceneNode*
	SceneNode::move(Real x, Real y, Real z)
	{
		move(Vector3(x, y, z));
		return this;
	}

	inline SceneNode*
	SceneNode::move(const Vector3& vector)
	{
		location += vector;
		markChanged(CHANGE_LOCATION);
		return this;
	}

	inline SceneNode*
	SceneNode::move(Real x, Real y, Real z, Real amount)
	{
		move(Vector3(x, y, z), amount);
		return this;
	}

	inline SceneNode*
	SceneNode::move(const Vector3& vector, Real amount)
	{
		move(vector * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::move(Real x, Real y, Real z, const SceneNode* context)
	{
		move(Vector3(x, y, z), context);
		return this;
	}

	inline SceneNode*
	SceneNode::move(const Vector3& vector, const SceneNode* context)
	{
		if (context == this)
		{
			return move(vector);
		}
		move(context->getRotation(root()) * vector);
		return this;
	}

	inline SceneNode*
	SceneNode::moveLeft(Real amount)
	{
		move(getLeftVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveLeft(Real amount, const SceneNode* context)
	{
		move(context->getLeftVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveRight(Real amount)
	{
		move(getRightVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveRight(Real amount, const SceneNode* context)
	{
		move(context->getRightVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveUp(Real amount)
	{
		move(getUpVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveUp(Real amount, const SceneNode* context)
	{
		move(context->getUpVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveDown(Real amount)
	{
		move(getDownVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveDown(Real amount, const SceneNode* context)
	{
		move(context->getDownVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveForward(Real amount)
	{
		move(getForwardVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveForward(Real amount, const SceneNode* context)
	{
		move(context->getForwardVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveBackward(Real amount)
	{
		move(getBackwardVector() * amount);
		return this;
	}

	inline SceneNode*
	SceneNode::moveBackward(Real amount, const SceneNode* context)
	{
		move(context->getBackwardVector() * amount);
		return this;
	}

	inline Vector3
	SceneNode::vectorTo(const SceneNode* destination) const
	{
		return destination->getLocation(root()) - getLocation(root());
	}

	inline Vector3
	SceneNode::vectorTo(const Vector3& destination) const
	{
		return destination - getLocation(root());
	}

	inline Vector3
	SceneNode::vectorTo(Real x, Real y, Real z) const
	{
		return vectorTo(Vector3(x, y, z));
	}

	inline Vector3
	SceneNode::getLocation() const
	{
		return location;
	}

	inline Vector3
	SceneNode::getLocation(const SceneNode* context) const
	{
		if (context == this)
		{
			return Vector3();
		}
		else if (context == parent)
		{
			return location;
		}
		else if (context == root())
		{
			return parent->getLocation(root()) + parent->orientation * location * parent->_scale;
		}
		else
		{
			getLocation(root()) - context->getLocation(root());
		}
	}

	inline SceneNode*
	SceneNode::setRotation(const Quaternion& q)
	{
		orientation = q;
		markChanged(CHANGE_ROTATION);
		return this;
	}

	inline SceneNode*
	SceneNode::rotate(const Quaternion& q)
	{
		rotate(q, this);
		return this;
	}

	inline SceneNode*
	SceneNode::rotate(const Quaternion& q, const SceneNode* context)
	{
		if (context == this)
		{
			orientation = orientation * q;
		}
		else if (context == parent)
		{
			orientation = q * orientation;
		}
		else
		{
			Quaternion r(getRotation(context));
			orientation *= r.getInverseRotation() * q * r;
		}
		markChanged(CHANGE_ROTATION);
		return this;
	}

	inline SceneNode*
	SceneNode::rotate(Angle angle, Vector3 axis)
	{
		rotate(angle, axis, this);
		return this;
	}

	inline SceneNode*
	SceneNode::rotate(Angle angle, Vector3 axis, const SceneNode* context)
	{
		if (angle.equals(Degree(0), Degree(0)))
		{
			return this;
		}
		rotate(Quaternion(angle, axis), context);
		return this;
	}

	inline SceneNode*
	SceneNode::rotateLeft(Angle amount)
	{
		return rotateLeft(amount, this);
	}

	inline SceneNode*
	SceneNode::rotateLeft(Angle amount, const SceneNode* context)
	{
		rotate(CoordinateSystem::get().isLeftHanded() ? amount : -amount, CoordinateSystem::get().getDownVector(), context);
		return this;
	}

	inline SceneNode*
	SceneNode::rotateRight(Angle amount)
	{
		rotateLeft(-amount);
		return this;
	}

	inline SceneNode*
	SceneNode::rotateRight(Angle amount, const SceneNode* context)
	{
		rotateLeft(-amount, context);
		return this;
	}

	inline SceneNode*
	SceneNode::rotateUp(Angle amount)
	{
		rotateUp(amount, this);
		return this;
	}

	inline SceneNode*
	SceneNode::rotateUp(Angle amount, const SceneNode* context)
	{
		rotate(CoordinateSystem::get().isLeftHanded() ? amount : -amount, CoordinateSystem::get().getLeftVector(), context);
		return this;
	}

	inline SceneNode*
	SceneNode::rotateDown(Angle amount)
	{
		return rotateUp(-amount);
	}

	inline SceneNode*
	SceneNode::rotateDown(Angle amount, const SceneNode* context)
	{
		return rotateUp(-amount, context);
	}

	inline SceneNode*
	SceneNode::tiltLeft(Angle amount)
	{
		return tiltLeft(amount, this);
	}

	inline SceneNode*
	SceneNode::tiltLeft(Angle amount, const SceneNode* context)
	{
		rotate(CoordinateSystem::get().isLeftHanded() ? amount : -amount, CoordinateSystem::get().getForwardVector(), context);
		return this;
	}

	inline SceneNode*
	SceneNode::tiltRight(Angle amount)
	{
		return tiltLeft(-amount);
	}

	inline SceneNode*
	SceneNode::tiltRight(Angle amount, const SceneNode* context)
	{
		return tiltLeft(-amount, context);
	}

	inline SceneNode*
	SceneNode::setDirection(const Vector3& direction, bool keepTilt)
	{
		if (keepTilt)
		{
			setDirection(direction, false);
			// TODO: finish implementation
		}
		else
		{
			Angle angle(direction.angleTo(getForwardVector()));
			rotate(CoordinateSystem::get().isLeftHanded() ? angle : -angle, direction.crossProduct(getForwardVector()), this);
		}
		return this;
	}

	inline SceneNode*
	SceneNode::setDirection(Real x, Real y, Real z, bool keepTilt)
	{
		setDirection(Vector3(x, y, z), keepTilt);
		return this;
	}

	inline SceneNode*
	SceneNode::lookAt(const SceneNode* target, bool keepTilt)
	{
		setDirection(vectorTo(target), keepTilt);
		return this;
	}

	inline SceneNode*
	SceneNode::lookAt(const Vector3& target, bool keepTilt)
	{
		setDirection(vectorTo(target), keepTilt);
		return this;
	}

	inline SceneNode*
	SceneNode::lookAt(Real x, Real y, Real z, bool keepTilt)
	{
		setDirection(vectorTo(Vector3(x, y, z)), keepTilt);
		return this;
	}

	inline Vector3
	SceneNode::getLeftVector() const
	{
		return CoordinateSystem::get().getLeftVector() * orientation;
	}

	inline Vector3
	SceneNode::getRightVector() const
	{
		return CoordinateSystem::get().getRightVector() * orientation;
	}

	inline Vector3
	SceneNode::getUpVector() const
	{
		return CoordinateSystem::get().getUpVector() * orientation;
	}

	inline Vector3
	SceneNode::getDownVector() const
	{
		return CoordinateSystem::get().getDownVector() * orientation;
	}

	inline Vector3
	SceneNode::getForwardVector() const
	{
		return CoordinateSystem::get().getForwardVector() * orientation;
	}

	inline Vector3
	SceneNode::getBackwardVector() const
	{
		return CoordinateSystem::get().getBackwardVector() * orientation;
	}

	inline Quaternion
	SceneNode::getRotation() const
	{
		return orientation;
	}

	inline Quaternion
	SceneNode::getRotation(const SceneNode* context) const
	{
		if (context == this)
		{
			return Quaternion();
		}
		else if (context == parent)
		{
			return orientation;
		}
		else if (context == root())
		{
			return parent->getRotation(root()) * orientation;
		}
		return context->getRotation(root()).getInverseRotation() * getRotation(root());
	}

	inline SceneNode*
	SceneNode::setScale(Real scale)
	{
		_scale = scale;
		markChanged(CHANGE_SCALE);
		return this;
	}

	inline SceneNode*
	SceneNode::setScale(Real scale, const SceneNode* context)
	{
		setScale(scale / getScale(context));
		return this;
	}

	inline SceneNode*
	SceneNode::scale(Real scale)
	{
		setScale(_scale * scale);
		return this;
	}

	inline Real
	SceneNode::getScale() const
	{
		return _scale;
	}

	inline Real
	SceneNode::getScale(const SceneNode* context) const
	{
		if (context == this)
		{
			return 1;
		}
		else if (context == parent)
		{
			return _scale;
		}
		else if (context == root())
		{
			return parent->getScale(root()) * _scale;
		}
		return getScale(root()) / context->getScale(root());
	}

}

#endif /* PURGE_SCENENODE_H */

