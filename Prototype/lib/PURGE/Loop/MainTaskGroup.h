#ifndef PURGE_MAINTASKGROUP_H
#define PURGE_MAINTASKGROUP_H 1

#include "TaskGroup.h"
#include "RenderingStartTask.h"
#include "RenderingFinishTask.h"
#include "FpsPrintTask.h"
#include "../Graphics/Window.h"
#include "../Graphics/Camera.h"
#include "../Graphics/CameraNode.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace PURGE
{

	class MainTaskGroup : public virtual TaskGroup
	{

		public:
			static MainTaskGroup* get();

			TaskGroup* add(Task* task);

			void loop();
			void stop();

			float timeSinceStart() const;
			float timeSinceLastCycle() const;

			virtual void perform();

			bool autoArrangeWindows;
			bool autoActivateRenderer;
			bool shutDownOnWindowClose;

		private:
			static MainTaskGroup* instance;

			MainTaskGroup();
			void arrangeWindows() const;
			void activateRenderer() const;

			bool stopping;

			boost::posix_time::ptime cycleStart;
			boost::posix_time::ptime lastCycleStart;
			boost::posix_time::ptime loopStart;

	};

	inline MainTaskGroup*
	MainTaskGroup::get()
	{
		if (!instance) {
			instance = new MainTaskGroup();
		}
		return instance;
	}

	inline TaskGroup*
	MainTaskGroup::add(Task* task)
	{
		return addBefore(RenderingFinishTask::get(), task);
	}

	inline
	MainTaskGroup::MainTaskGroup()
	             : autoArrangeWindows(true)
	             , autoActivateRenderer(true)
	             , shutDownOnWindowClose(true)
	{
		tasks.push_back(RenderingStartTask::get());
		tasks.push_back(RenderingFinishTask::get());
	}

	inline void
	MainTaskGroup::loop()
	{
		stopping = false;
		loopStart = lastCycleStart = cycleStart = boost::posix_time::microsec_clock::local_time();
		if (autoArrangeWindows)
		{
			arrangeWindows();
		}
		if (autoActivateRenderer)
		{
			activateRenderer();
		}
		while (!stopping)
		{
			perform();
			if (shutDownOnWindowClose && Window::allInstancesClosed())
			{
				stop();
			}
		}
	}

	inline void
	MainTaskGroup::perform()
	{
		cycleStart = boost::posix_time::microsec_clock::local_time();
		TaskGroup::perform();
		lastCycleStart = cycleStart;
	}

	inline void
	MainTaskGroup::activateRenderer() const
	{
		if (Renderer::getActiveInstance())
		{
			return;
		}
		auto renderers = Renderer::getAllInstances();
		if (renderers.empty())
		{
			throw "No renderer found";
		}
		(*renderers.begin())->activate();
	}

	inline void
	MainTaskGroup::arrangeWindows() const
	{
		if (CameraNode::getAllInstances().empty())
		{
			Camera::create();
		}
		if (Window::getAllInstances().empty())
		{
			Window::create(CameraNode::getAllInstances());
		}
		else
		{
			std::list<Window*> windowsWithoutViewports(Window::getAllInstances());
			std::list<CameraNode*> unusedCameraNodes(CameraNode::getAllInstances());
			// bool hasViewports(const Window*& window) {return window->getAllViewports().size() > 0};
			// windowsWithoutViewports.remove_if(hasViewports);
			for (auto w = windowsWithoutViewports.begin(); w != windowsWithoutViewports.end(); w++)
			{
				if ((*w)->getAllViewports().size() == 0)
				{
					continue;
				}
				for (auto v = (*w)->getAllViewports().begin(); v != (*w)->getAllViewports().end(); v++)
				{
					for (auto c = unusedCameraNodes.begin(); c != unusedCameraNodes.end(); c++)
					{
						if (*c == (*v)->getCamera())
						{
							c = unusedCameraNodes.erase(c);
							c--;
						}
					}
				}
				w = windowsWithoutViewports.erase(w);
				w--;
			}
			if (windowsWithoutViewports.size() >= unusedCameraNodes.size())
			{
				auto w = windowsWithoutViewports.begin();
				for (auto c = unusedCameraNodes.begin(); c != unusedCameraNodes.end(); c++, w++)
				{
					(*w)->createViewport(*c);
				}
			}
			else
			{
				throw "MainTaskGroup: Assigning multiple cameras to windows is not implemented yet";
			}
		}
	}

	inline void
	MainTaskGroup::stop()
	{
		stopping = true;
	}

	inline float
	MainTaskGroup::timeSinceStart() const
	{
		return (cycleStart - loopStart).total_microseconds() / 1000000.0;
	}

	inline float
	MainTaskGroup::timeSinceLastCycle() const
	{
		return (cycleStart - lastCycleStart).total_microseconds() / 1000000.0;
	}

}

#endif /* PURGE_MAINTASKGROUP_H */

