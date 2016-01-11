#ifndef PURGE_TASKGROUP_H
#define PURGE_TASKGROUP_H 1

#include "Task.h"
#include <list>

namespace PURGE
{

	class TaskGroup : public virtual Task
	{

		public:
			virtual ~TaskGroup();

			virtual void perform();
			virtual TaskGroup* add(Task* task);
			virtual TaskGroup* addBefore(Task* otherTask, Task* task);
			virtual TaskGroup* addAfter(Task* otherTask, Task* task);
			virtual TaskGroup* remove(Task* task);

		protected:
			std::list<Task*> tasks;

	};

	inline
	TaskGroup::~TaskGroup()
	{}

	inline TaskGroup*
	TaskGroup::add(Task* task)
	{
		tasks.push_back(task);
		return this;
	}

	inline TaskGroup*
	TaskGroup::addBefore(Task* otherTask, Task* task)
	{
		for (auto i = tasks.begin(); i != tasks.end(); i++)
		{
			if ((*i) == otherTask)
			{
				tasks.insert(i, task);
			}
		}
		return this;
	}

	inline TaskGroup*
	TaskGroup::addAfter(Task* otherTask, Task* task)
	{
		for (auto i = tasks.begin(); i != tasks.end(); i++)
		{
			if ((*i) == otherTask)
			{
				tasks.insert(++i, task);
			}
		}
		return this;
	}

	inline TaskGroup*
	TaskGroup::remove(Task* task)
	{
		tasks.remove(task);
		return this;
	}

	inline void
	TaskGroup::perform()
	{
		for (auto i = tasks.begin(); i != tasks.end(); i++)
		{
			(*i)->perform();
		}
	}

}

#endif /* PURGE_TASKGROUP_H */

