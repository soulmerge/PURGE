#ifndef PURGE_RENDERINGFINISHTASK_H
#define PURGE_RENDERINGFINISHTASK_H 1

#include "Task.h"
#include "../Graphics/Renderer.h"

namespace PURGE
{

	class RenderingFinishTask : public virtual Task
	{

		public:
			static RenderingFinishTask* get();

			void perform();

		private:
			static RenderingFinishTask* instance;

			RenderingFinishTask();


	};

	inline RenderingFinishTask*
	RenderingFinishTask::get()
	{
		if (!instance) {
			instance = new RenderingFinishTask();
		}
		return instance;
	}

	inline
	RenderingFinishTask::RenderingFinishTask()
	{}

	inline void
	RenderingFinishTask::perform()
	{
		if (Renderer::getActiveInstance())
		{
			Renderer::getActiveInstance()->finishRendering();
		}
	}

}

#endif /* PURGE_RENDERINGFINISHTASK_H */

