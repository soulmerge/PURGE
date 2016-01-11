#ifndef PURGE_FPSPRINTTASK_H
#define PURGE_FPSPRINTTASK_H 1

#include "Task.h"

namespace PURGE
{

	class FpsPrintTask : public virtual Task
	{

		public:
			static FpsPrintTask* create();

			void perform();

		private:
			static FpsPrintTask* instance;
			FpsPrintTask();

			int count;
			float time;

	};

	inline FpsPrintTask*
	FpsPrintTask::create()
	{
		if (!instance) {
			instance = new FpsPrintTask();
		}
		return instance;
	}

	inline
	FpsPrintTask::FpsPrintTask()
	{}

}

#endif /* PURGE_FPSPRINTTASK_H */

