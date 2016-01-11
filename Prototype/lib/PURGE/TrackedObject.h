#ifndef PURGE_TRACKEDOBJECT_H
#define PURGE_TRACKEDOBJECT_H 1

#include <list>
#include <memory>
#include <iostream>

namespace PURGE
{

	template<class T>
	class TrackedObject
	{

		public:
			static std::list<T*> getAllInstances();
			static std::list<T*> getNewInstances();
			static std::list<T*> getUpdatedInstances();
			static std::list<T*> getDestroyedInstances();
			static void prepareCycleChanges();
			static void clearCycleChanges();

			std::list<int> getChanges() const;

			virtual ~TrackedObject();
			void destroy();

		protected:
			TrackedObject();
			void init();
			void markChanged(int change);

		private:
			static std::list<T*> allInstances;
			static std::list<T*> newInstances;
			static std::list<T*> updatedInstances;
			static std::list<T*> destroyedInstances;

			std::list<int> changes;
			bool isNew;

	};

	template<class T> inline std::list<T*>
	TrackedObject<T>::getAllInstances()
	{
		return allInstances;
	}

	template<class T> inline std::list<T*>
	TrackedObject<T>::getNewInstances()
	{
		return newInstances;
	}

	template<class T> inline std::list<T*>
	TrackedObject<T>::getUpdatedInstances()
	{
		return updatedInstances;
	}

	template<class T> inline std::list<T*>
	TrackedObject<T>::getDestroyedInstances()
	{
		return destroyedInstances;
	}

	template<class T> inline void
	TrackedObject<T>::prepareCycleChanges()
	{
		for (auto destroyed = destroyedInstances.begin(); destroyed != destroyedInstances.end(); destroyed++)
		{
			newInstances.remove(*destroyed);
		}
		for (auto updated1 = updatedInstances.begin(); updated1 != updatedInstances.end(); updated1++)
		{
			auto updated2 = updated1;
			for (updated2++; updated2 != updatedInstances.end(); updated2++)
			{
				if ((*updated2) == (*updated1))
				{
					updated2 = updatedInstances.erase(updated2);
					updated2--;
				}
			}
		}
	}

	template<class T> inline void
	TrackedObject<T>::clearCycleChanges()
	{
		for (auto i = newInstances.begin(); i != newInstances.end(); i++)
		{
			(*i)->isNew = false;
		}
		updatedInstances.clear();
		newInstances.clear();
		destroyedInstances.clear();
	}

	template<class T> inline
	TrackedObject<T>::~TrackedObject()
	{}

	template<class T> inline std::list<int>
	TrackedObject<T>::getChanges() const
	{
		return changes;
	}

	template<class T> inline void
	TrackedObject<T>::destroy()
	{
		destroyedInstances.push_back(this);
	}

	template<class T> inline
	TrackedObject<T>::TrackedObject()
	                : isNew(true)
	{}

	template<class T> inline void
	TrackedObject<T>::init()
	{
		T* p(dynamic_cast<T*>(const_cast<TrackedObject<T>*>(this)));
		allInstances.push_back(p);
		newInstances.push_back(p);
	}

	template<class T> inline void
	TrackedObject<T>::markChanged(int change)
	{
		if (isNew)
		{
			return;
		}
		changes.push_back(change);
		updatedInstances.push_back(dynamic_cast<T*>(this));
	}

	template<class T> std::list<T*>
	TrackedObject<T>::allInstances = std::list<T*>();

	template<class T> std::list<T*>
	TrackedObject<T>::newInstances = std::list<T*>();

	template<class T> std::list<T*>
	TrackedObject<T>::updatedInstances = std::list<T*>();

	template<class T> std::list<T*>
	TrackedObject<T>::destroyedInstances = std::list<T*>();

}

#endif /* PURGE_TRACKEDOBJECT_H */

