#ifndef PURGE_CAMERA_H
#define PURGE_CAMERA_H 1

#include "../classes.h"
#include "../Math/Real.h"

namespace PURGE
{

	class Camera
	{

		public:
			static CameraNode* create();

			virtual ~Camera();

			virtual Camera* setVisibleRange(Real min, Real max) = 0;

			virtual Real getMinVisibleRange() const = 0;
			virtual Real getMaxVisibleRange() const = 0;

	};

	inline
	Camera::~Camera()
	{}

}

#endif /* PURGE_CAMERA_H */

