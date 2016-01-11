#ifndef PURGE_RENDERINGSTARTTASK
#define PURGE_RENDERINGSTARTTASK 1

#include "Task.h"
#include "../Graphics/Renderer.h"
#include "../Space/SceneNode.h"
#include "../Graphics/Window.h"
#include "../Graphics/CameraDefinition.h"
#include "../Graphics/ModelDefinition.h"
#include "../Graphics/SpotLightDefinition.h"

namespace PURGE
{

	class RenderingStartTask : public virtual Task
	{

		public:
			static RenderingStartTask* get();

			void perform();

		private:
			static RenderingStartTask* instance;

			RenderingStartTask();

	};

	inline RenderingStartTask*
	RenderingStartTask::get()
	{
		if (!instance) {
			instance = new RenderingStartTask();
		}
		return instance;
	}

	inline
	RenderingStartTask::RenderingStartTask()
	{}

	inline void
	RenderingStartTask::perform()
	{
		SceneNode::prepareCycleChanges();
		CameraDefinition::prepareCycleChanges();
		ModelDefinition::prepareCycleChanges();
		SpotLightDefinition::prepareCycleChanges();
		Window::prepareCycleChanges();
		Window::Viewport::prepareCycleChanges();
		if (Renderer::getActiveInstance())
		{
			Renderer::getActiveInstance()->startRendering();
		}
		SceneNode::clearCycleChanges();
		CameraDefinition::clearCycleChanges();
		ModelDefinition::clearCycleChanges();
		SpotLightDefinition::clearCycleChanges();
		Window::clearCycleChanges();
		Window::Viewport::clearCycleChanges();
	}

}

#endif /* PURGE_RENDERINGSTARTTASK */

