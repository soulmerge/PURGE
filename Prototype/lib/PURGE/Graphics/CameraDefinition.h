#ifndef PURGE_CAMERADEFINITION_H
#define PURGE_CAMERADEFINITION_H 1

#include "../classes.h"
#include "../Space/SceneNode.h"
#include "../TrackedObject.h"
#include "Camera.h"

namespace PURGE
{

	class CameraDefinition : public virtual Camera, public virtual TrackedObject<CameraDefinition>
	{

		public:
            static const int CHANGE_VISIBLERANGE = 0x1;
			static CameraDefinition* create();

			Camera* setVisibleRange(Real min, Real max);

			Real getMinVisibleRange() const;
			Real getMaxVisibleRange() const;

		private:
			CameraDefinition();

			Real minVisibleRange;
			Real maxVisibleRange;

	};

	inline CameraDefinition*
	CameraDefinition::create()
	{
		return new CameraDefinition();
	}

	inline
	CameraDefinition::CameraDefinition()
	                : minVisibleRange(0.1)
	                , maxVisibleRange(0)
	{
		init();
	}

	inline Camera*
	CameraDefinition::setVisibleRange(Real min, Real max)
	{
		minVisibleRange = min;
		maxVisibleRange = max;
        markChanged(CHANGE_VISIBLERANGE);
		return this;
	}

	inline Real
	CameraDefinition::getMinVisibleRange() const
	{
		return minVisibleRange;
	}

	inline Real
	CameraDefinition::getMaxVisibleRange() const
	{
		return maxVisibleRange;
	}

}

#endif /* PURGE_CAMERADEFINITION_H */

