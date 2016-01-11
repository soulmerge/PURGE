#ifndef PURGE_COORDINATESYSTEM_H
#define PURGE_COORDINATESYSTEM_H 1

#include "../classes.h"
#include "../Math/Vector3.h"

namespace PURGE
{

	class CoordinateSystem
	{

		public:

			enum Direction
			{
				left,
				right,
				up,
				down,
				forward,
				backward
			};

			// Names consist of forward, right and up coordinates, with N for negative and P for positive values
			// NZ_PX_PY: (OpenGL Coordinate System)
			//   Forward = Negative Z
			//   Right = Positive X
			//   Up = Positive Y
			static const CoordinateSystem PX_PY_PZ;
			static const CoordinateSystem PX_PY_NZ;
			static const CoordinateSystem PX_NY_PZ;
			static const CoordinateSystem PX_NY_NZ;
			static const CoordinateSystem NX_PY_PZ;
			static const CoordinateSystem NX_PY_NZ;
			static const CoordinateSystem NX_NY_PZ;
			static const CoordinateSystem NX_NY_NZ;
			static const CoordinateSystem PX_PZ_PY;
			static const CoordinateSystem PX_PZ_NY;
			static const CoordinateSystem PX_NZ_PY;
			static const CoordinateSystem PX_NZ_NY;
			static const CoordinateSystem NX_PZ_PY;
			static const CoordinateSystem NX_PZ_NY;
			static const CoordinateSystem NX_NZ_PY;
			static const CoordinateSystem NX_NZ_NY;
			static const CoordinateSystem PY_PX_PZ;
			static const CoordinateSystem PY_PX_NZ;
			static const CoordinateSystem PY_NX_PZ;
			static const CoordinateSystem PY_NX_NZ;
			static const CoordinateSystem NY_PX_PZ;
			static const CoordinateSystem NY_PX_NZ;
			static const CoordinateSystem NY_NX_PZ;
			static const CoordinateSystem NY_NX_NZ;
			static const CoordinateSystem PY_PZ_PX;
			static const CoordinateSystem PY_PZ_NX;
			static const CoordinateSystem PY_NZ_PX;
			static const CoordinateSystem PY_NZ_NX;
			static const CoordinateSystem NY_PZ_PX;
			static const CoordinateSystem NY_PZ_NX;
			static const CoordinateSystem NY_NZ_PX;
			static const CoordinateSystem NY_NZ_NX;
			static const CoordinateSystem PZ_PX_PY;
			static const CoordinateSystem PZ_PX_NY;
			static const CoordinateSystem PZ_NX_PY;
			static const CoordinateSystem PZ_NX_NY;
			static const CoordinateSystem NZ_PX_PY;
			static const CoordinateSystem NZ_PX_NY;
			static const CoordinateSystem NZ_NX_PY;
			static const CoordinateSystem NZ_NX_NY;
			static const CoordinateSystem PZ_PY_PX;
			static const CoordinateSystem PZ_PY_NX;
			static const CoordinateSystem PZ_NY_PX;
			static const CoordinateSystem PZ_NY_NX;
			static const CoordinateSystem NZ_PY_PX;
			static const CoordinateSystem NZ_PY_NX;
			static const CoordinateSystem NZ_NY_PX;
			static const CoordinateSystem NZ_NY_NX;
			static const CoordinateSystem& OpenGL;
			static const CoordinateSystem& DirectX;

			static const CoordinateSystem& get();
			static void set(const CoordinateSystem&);

			Direction getXDirection() const;
			Direction getYDirection() const;
			Direction getZDirection() const;
			Vector3 getVector(Direction d) const;
			Vector3 getLeftVector() const;
			Vector3 getRightVector() const;
			Vector3 getUpVector() const;
			Vector3 getDownVector() const;
			Vector3 getForwardVector() const;
			Vector3 getBackwardVector() const;
			bool isLeftHanded() const;

		private:
			static const CoordinateSystem* _current;

			CoordinateSystem(const Vector3& forward, const Vector3& right, const Vector3& up, bool leftHanded);
			CoordinateSystem(const CoordinateSystem&);
			CoordinateSystem& operator=(const CoordinateSystem&);

			Vector3 forwardVector;
			Vector3 rightVector;
			Vector3 upVector;
			bool leftHanded;

	};

	inline
	CoordinateSystem::CoordinateSystem(const Vector3& forward, const Vector3& right, const Vector3& up, bool leftHanded)
	                : forwardVector(forward)
	                , rightVector(right)
	                , upVector(up)
	                , leftHanded(leftHanded)
	{}

	inline const CoordinateSystem&
	CoordinateSystem::get()
	{
		return *_current;
	}

	inline void
	CoordinateSystem::set(const CoordinateSystem& coordinateSystem)
	{
		_current = &coordinateSystem;
	}

	inline CoordinateSystem::Direction
	CoordinateSystem::getXDirection() const
	{
		if (forwardVector.x() == 1)
		{
			return forward;
		}
		else if (rightVector.x() == 1)
		{
			return right;
		}
		else if (upVector.x() == 1)
		{
			return up;
		}
		else if (rightVector.x() == -1)
		{
			return left;
		}
		else if (upVector.x() == -1)
		{
			return down;
		}
		else // if (forwardVector.x() == -1)
		{
			return backward;
		}
	}

	inline CoordinateSystem::Direction
	CoordinateSystem::getYDirection() const
	{
		if (forwardVector.y() == 1)
		{
			return forward;
		}
		else if (rightVector.y() == 1)
		{
			return right;
		}
		else if (upVector.y() == 1)
		{
			return up;
		}
		else if (rightVector.y() == -1)
		{
			return left;
		}
		else if (upVector.y() == -1)
		{
			return down;
		}
		else // if (forwardVector.y() == -1)
		{
			return backward;
		}
	}

	inline CoordinateSystem::Direction
	CoordinateSystem::getZDirection() const
	{
		if (forwardVector.z() == 1)
		{
			return forward;
		}
		else if (rightVector.z() == 1)
		{
			return right;
		}
		else if (upVector.z() == 1)
		{
			return up;
		}
		else if (rightVector.z() == -1)
		{
			return left;
		}
		else if (upVector.z() == -1)
		{
			return down;
		}
		else // if (forwardVector.z() == -1)
		{
			return backward;
		}
	}

	inline Vector3
	CoordinateSystem::getVector(Direction d) const
	{
		switch (d)
		{
			case forward:
				return forwardVector;
			case backward:
				return -forwardVector;
			case right:
				return rightVector;
			case left:
				return -rightVector;
			case up:
				return upVector;
			case down:
				return -upVector;
			default:
				throw "Unknown direction";
		}
	}

	inline Vector3
	CoordinateSystem::getLeftVector() const
	{
		return getVector(left);
	}

	inline Vector3
	CoordinateSystem::getRightVector() const
	{
		return getVector(right);
	}

	inline Vector3
	CoordinateSystem::getUpVector() const
	{
		return getVector(up);
	}

	inline Vector3
	CoordinateSystem::getDownVector() const
	{
		return getVector(down);
	}

	inline Vector3
	CoordinateSystem::getForwardVector() const
	{
		return getVector(forward);
	}

	inline Vector3
	CoordinateSystem::getBackwardVector() const
	{
		return getVector(backward);
	}

	inline bool
	CoordinateSystem::isLeftHanded() const
	{
		return leftHanded;
	}

}

#endif /* PURGE_COORDINATESYSTEM_H */

