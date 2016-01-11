#ifndef PURGE_RENDERER_H
#define PURGE_RENDERER_H 1

#include "../classes.h"
#include <vector>

#include <iostream>

namespace PURGE
{

	class Renderer
	{

		public:
			static Renderer* getActiveInstance();
			static std::vector<Renderer*> getAllInstances();

			Renderer();
			virtual ~Renderer();

			void activate();
			void deactivate();

			virtual bool windowIsClosed(const Window* window, bool currentStatus) const = 0;
			virtual void startRendering() = 0;
			virtual void finishRendering() = 0;

		protected:
			virtual void _activate() = 0;
			virtual void _deactivate() = 0;

		private:
			static Renderer* activeInstance;
			static std::vector<Renderer*> instances;

	};

	inline
	Renderer::Renderer()
	{
		instances.push_back(this);
	}

	inline
	Renderer::~Renderer()
	{
		for (auto renderer = instances.begin(); renderer != instances.end(); renderer++)
		{
			if ((*renderer) == this)
			{
				instances.erase(renderer);
				break;
			}
		}
	}

	inline void
	Renderer::deactivate()
	{
		if (activeInstance != this)
		{
			return;
		}
		_deactivate();
	}

	inline Renderer*
	Renderer::getActiveInstance()
	{
		return activeInstance;
	}

	inline std::vector<Renderer*>
	Renderer::getAllInstances()
	{
		return instances;
	}

}

#endif /* PURGE_RENDERER_H */

