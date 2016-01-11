#include "Renderer.h"

#include "../Space/SceneNode.h"
#include "CameraDefinition.h"
#include "ModelDefinition.h"
#include "SpotLightDefinition.h"
#include "Window.h"

namespace PURGE
{

	Renderer*
	Renderer::activeInstance;

	std::vector<Renderer*>
	Renderer::instances;

	void
	Renderer::activate()
	{
		if (activeInstance == this)
		{
			return;
		}
		if (activeInstance)
		{
			activeInstance->deactivate();
		}
		SceneNode::clearCycleChanges();
		CameraDefinition::clearCycleChanges();
		ModelDefinition::clearCycleChanges();
		SpotLightDefinition::clearCycleChanges();
		Window::clearCycleChanges();
		Window::Viewport::clearCycleChanges();
		_activate();
		activeInstance = this;
	}

}

