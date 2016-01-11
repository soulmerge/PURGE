#ifndef PURGE_MODEL_H
#define PURGE_MODEL_H 1

#include "../classes.h"

namespace PURGE
{

	class Model
	{

		public:
			static ModelNode* load(std::string name);

			virtual ~Model();

			virtual std::string getName() const = 0;

	};

}

#include "ModelNode.h"
#include "ModelDefinition.h"

namespace PURGE
{

	inline
	Model::~Model()
	{}

}

#endif /* PURGE_MODEL_H */

