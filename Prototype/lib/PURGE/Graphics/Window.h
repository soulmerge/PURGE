#ifndef PURGE_WINDOW_H
#define PURGE_WINDOW_H 1

#include "../classes.h"
#include "../TrackedObject.h"
#include "Camera.h"
#include "CameraNode.h"
#include <vector>

namespace PURGE
{

	class Window : public virtual TrackedObject<Window>
	{

		public:

			class Viewport : public virtual TrackedObject<Viewport>
			{

				public:
					static Viewport* create(Window* window, CameraNode* camera);
					static Viewport* create(Window* window, CameraNode* camera, Real width, Real height);

					Window* getWindow() const;
					CameraNode* getCamera() const;
					Real getWidth() const;
					Real getHeight() const;

				private:
					Viewport(Window* window, CameraNode* camera, Real width, Real height);

					Window* window;
					CameraNode* camera;
					Real width;
					Real height;

			};

			static Window* create();
			static Window* create(std::list<CameraNode*> cameras);
			static Window* create(int width, int height);

			static bool allInstancesClosed();

			Viewport* createViewport(CameraNode* camera);
			Viewport* createViewport(CameraNode* camera, Real width, Real height);

			std::list<Viewport*> getAllViewports() const;
			std::list<Viewport*> getNewViewports() const;
			std::list<Viewport*> getUpdatedViewports() const;
			std::list<Viewport*> getDestroyedViewports() const;

			int getWidth() const;
			int getHeight() const;
			bool isClosed() const;

		private:
			Window(int width, int height);

			std::list<Viewport*> filterOwnViewports(std::list<Viewport*> viewports) const;

			int width;
			int height;
			mutable bool closed;

	};

	inline Window*
	Window::create()
	{
		return create(800, 600);
	}

	inline Window*
	Window::create(std::list<CameraNode*> cameras)
	{
		Window* w(create());
		if (cameras.size() == 1)
		{
			w->createViewport(*cameras.begin());
		}
		return w;
	}

	inline Window*
	Window::create(int width, int height)
	{
		return new Window(width, height);
	}

	inline bool
	Window::allInstancesClosed()
	{
		for (auto w = Window::getAllInstances().begin(); w != Window::getAllInstances().end(); w++)
		{
			if (!(*w)->isClosed())
			{
				return false;
			}
		}
		return true;
	}

	inline
	Window::Window(int width, int height)
	      : width(width)
	      , height(height)
	{
		init();
	}

	inline Window::Viewport*
	Window::createViewport(CameraNode* camera)
	{
		return Viewport::create(this, camera);
	}

	inline Window::Viewport*
	Window::createViewport(CameraNode* camera, Real width, Real height)
	{
		return Viewport::create(this, camera, width, height);
	}

	inline std::list<Window::Viewport*>
	Window::getAllViewports() const
	{
		return filterOwnViewports(Viewport::getAllInstances());
	}

	inline std::list<Window::Viewport*>
	Window::getNewViewports() const
	{
		return filterOwnViewports(Viewport::getNewInstances());
	}

	inline std::list<Window::Viewport*>
	Window::getUpdatedViewports() const
	{
		return filterOwnViewports(Viewport::getUpdatedInstances());
	}

	inline std::list<Window::Viewport*>
	Window::getDestroyedViewports() const
	{
		return filterOwnViewports(Viewport::getDestroyedInstances());
	}

	inline std::list<Window::Viewport*>
	Window::filterOwnViewports(std::list<Viewport*> in) const
	{
		std::list<Window::Viewport*> out;
		for (auto i = in.begin(); i != in.end(); i++)
		{
			if ((*i)->getWindow() == this)
			{
				out.push_back(*i);
			}
		}
		return out;
	}

	inline int
	Window::getWidth() const
	{
		return width;
	}

	inline int
	Window::getHeight() const
	{
		return height;
	}

	inline Window::Viewport*
	Window::Viewport::create(Window* window, CameraNode* camera)
	{
		return create(window, camera, 1.0, 1.0);
	}

	inline Window::Viewport*
	Window::Viewport::create(Window* window, CameraNode* camera, Real width, Real height)
	{
		return new Window::Viewport(window, camera, width, height);
	}

	inline Window*
	Window::Window::Viewport::getWindow() const
	{
		return window;
	}

	inline CameraNode*
	Window::Viewport::getCamera() const
	{
		return camera;
	}

	inline Real
	Window::Viewport::getWidth() const
	{
		return width;
	}

	inline Real
	Window::Viewport::getHeight() const
	{
		return height;
	}

	inline
	Window::Viewport::Viewport(Window* window, CameraNode* camera, Real width, Real height)
	        : window(window)
	        , camera(camera)
	        , width(width)
	        , height(height)
	{
		assert(width >= 0 && width <= 1);
		assert(height >= 0 && height <= 1);
		init();
	}

}

#include "Renderer.h"

namespace PURGE
{

	inline bool
	Window::isClosed() const
	{
		auto renderer = Renderer::getActiveInstance();
		if (renderer)
		{
			return closed = renderer->windowIsClosed(this, closed);
		}
		return closed;
	}

}

#endif /* PURGE_WINDOW_H */

