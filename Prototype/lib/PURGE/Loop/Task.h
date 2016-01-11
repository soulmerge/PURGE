#ifndef PURGE_TASK_H
#define PURGE_TASK_H 1

#include "../classes.h"

namespace PURGE
{

	class Task
	{

		public:
			virtual ~Task();

			virtual void perform() = 0;

	};

	inline
	Task::~Task()
	{}

}

#endif /* PURGE_TASK_H */

