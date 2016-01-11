#ifndef PURGEBRIDGE_OGRE_1_7_TRANSCRIPTION_H
#define PURGEBRIDGE_OGRE_1_7_TRANSCRIPTION_H 1

#include "classes.h"
#include <map>
#include <iostream>
#include <PURGE/include.h>

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		template<class Original, class Transcript>
		class Transcription
		{

			public:
				static Transcript* create(Original* original);
				static Transcript* getTranscript(Original* original);
				static Transcript* getTranscript(const Original* original);
				static void activateInstances();
				static void updateInstances();

				virtual ~Transcription();
			
				virtual void update();

			protected:
				Transcription(Original* original);

				virtual void update(int change) = 0;
				virtual void destroy() = 0;

				Original* original;

				static std::map<Original*, Transcript*> instances;

		};

		template<class Original, class Transcript>
		Transcription<Original, Transcript>::~Transcription()
		{}

		template<class Original, class Transcript> Transcript*
		Transcription<Original, Transcript>::create(Original* original)
		{
			Transcript* c = new Transcript(original);
			instances[original] = c;
			return c;
		}

		template<class Original, class Transcript> Transcript*
		Transcription<Original, Transcript>::getTranscript(Original* original)
		{
			return instances[original];
		}

		template<class Original, class Transcript> Transcript*
		Transcription<Original, Transcript>::getTranscript(const Original* original)
		{
			return instances[const_cast<Original*>(original)];
		}

		template<class Original, class Transcript> void
		Transcription<Original, Transcript>::activateInstances()
		{
			auto created = Original::getAllInstances();
			for (auto i = created.begin(); i != created.end(); i++)
			{
				Transcript::create(*i);
			}
		}

		template<class Original, class Transcript> void
		Transcription<Original, Transcript>::updateInstances()
		{
			auto created = Original::getNewInstances();
			auto updated = Original::getUpdatedInstances();
			auto destroyed = Original::getDestroyedInstances();
			for (auto i = created.begin(); i != created.end(); i++)
			{
				Transcript::create(*i);
			}
			for (auto i = updated.begin(); i != updated.end(); i++)
			{
				dynamic_cast<Transcription<Original, Transcript>*>(instances[*i])->update();
			}
			for (auto i = destroyed.begin(); i != destroyed.end(); i++)
			{
				instances[*i]->destroy();
			}
		}

		template<class Original, class Transcript>
		Transcription<Original, Transcript>::Transcription(Original* original)
		          : original(original)
		{}

		template<class Original, class Transcript> void
		Transcription<Original, Transcript>::update()
		{
			auto changes = original->getChanges();
			for (auto change = changes.begin(); change != changes.end(); change++)
			{
				update(*change);
			}
		}

		template<class Original, class Transcript> std::map<Original*, Transcript*>
		Transcription<Original, Transcript>::instances = std::map<Original*, Transcript*>();

	}

}

#endif /* PURGEBRIDGE_OGRE_1_7_TRANSCRIPTION_H */

