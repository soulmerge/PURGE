#include "FpsPrintTask.h"

#include "MainTaskGroup.h"

namespace PURGE
{

	FpsPrintTask*
	FpsPrintTask::instance;

	void
	FpsPrintTask::perform()
	{
		count++;
		time += MainTaskGroup::get()->timeSinceLastCycle();
		if (time >= 1.0)
		{
			std::cout << (((float) count) / time) << " fps" << std::endl;
			count = 0;
			time = 0;
		}
	}

}

