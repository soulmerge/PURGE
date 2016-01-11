#ifndef PURGE_MODELDEFINITION_H
#define PURGE_MODELDEFINITION_H 1

#include "../classes.h"
#include "../Space/SceneNode.h"
#include "Model.h"
#include "../TrackedObject.h"
#include <map>

namespace PURGE
{

	class ModelDefinition : public virtual Model, public virtual TrackedObject<ModelDefinition>
	{

		public:
			static ModelDefinition* load(std::string name);

			virtual std::string getName() const;

		private:
			ModelDefinition(std::string name);

			std::string name;

			static std::map<std::string, ModelDefinition*> loadedModels;

	};

	inline ModelDefinition*
	ModelDefinition::load(std::string name)
	{
		auto iter = loadedModels.find(name);
		if (iter == loadedModels.end()) {
			loadedModels[name] = new ModelDefinition(name);
		}
		return loadedModels[name];
	}

	inline
	ModelDefinition::ModelDefinition(std::string name)
	               : name(name)
	{
		init();
	}

	inline std::string
	ModelDefinition::getName() const
	{
		return name;
	}

}

#endif /* PURGE_MODELDEFINITION_H */

