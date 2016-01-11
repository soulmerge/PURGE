#ifndef PURGE_MODELMODIFICATIONTASK_H
#define PURGE_MODELMODIFICATIONTASK_H 1

#include "../Math/Real.h"
#include "../Math/Vector3.h"
#include "MainTaskGroup.h"

namespace PURGE
{

	class SceneNodeModificationTask : public virtual Task
	{

		public:
			static SceneNodeModificationTask* create();
			static SceneNodeModificationTask* create(SceneNode* node);

			~SceneNodeModificationTask();

			void perform();

			SceneNodeModificationTask* registerNode(SceneNode* node);
			SceneNodeModificationTask* unregisterNode(SceneNode* node);

			// Location
			SceneNodeModificationTask* move(const Vector3& vector);
			SceneNodeModificationTask* move(Real x, Real y, Real z);
			SceneNodeModificationTask* move(const Vector3& vector, Real amount);
			SceneNodeModificationTask* move(Real x, Real y, Real z, Real amount);
			SceneNodeModificationTask* move(const Vector3& vector, const SceneNode* context);
			SceneNodeModificationTask* move(Real x, Real y, Real z, const SceneNode* context);
			SceneNodeModificationTask* moveLeft(Real amount);
			SceneNodeModificationTask* moveLeft(Real amount, const SceneNode* context);
			SceneNodeModificationTask* moveRight(Real amount);
			SceneNodeModificationTask* moveRight(Real amount, const SceneNode* context);
			SceneNodeModificationTask* moveUp(Real amount);
			SceneNodeModificationTask* moveUp(Real amount, const SceneNode* context);
			SceneNodeModificationTask* moveDown(Real amount);
			SceneNodeModificationTask* moveDown(Real amount, const SceneNode* context);
			SceneNodeModificationTask* moveForward(Real amount);
			SceneNodeModificationTask* moveForward(Real amount, const SceneNode* context);
			SceneNodeModificationTask* moveBackward(Real amount);
			SceneNodeModificationTask* moveBackward(Real amount, const SceneNode* context);

			// Rotation
			SceneNodeModificationTask* rotate(Angle angle, Vector3 axis);
			SceneNodeModificationTask* rotate(Angle angle, Vector3 axis, const SceneNode* viewPoint);
			SceneNodeModificationTask* rotateAroundX(Angle amount);
			SceneNodeModificationTask* rotateAroundY(Angle amount);
			SceneNodeModificationTask* rotateAroundZ(Angle amount);
			SceneNodeModificationTask* rotateLeft(Angle amount);
			SceneNodeModificationTask* rotateLeft(Angle amount, const SceneNode* viewPoint);
			SceneNodeModificationTask* rotateRight(Angle amount);
			SceneNodeModificationTask* rotateRight(Angle amount, const SceneNode* viewPoint);
			SceneNodeModificationTask* rotateUp(Angle amount);
			SceneNodeModificationTask* rotateUp(Angle amount, const SceneNode* viewPoint);
			SceneNodeModificationTask* rotateDown(Angle amount);
			SceneNodeModificationTask* rotateDown(Angle amount, const SceneNode* viewPoint);
			SceneNodeModificationTask* tiltLeft(Angle amount);
			SceneNodeModificationTask* tiltLeft(Angle amount, const SceneNode* viewPoint);
			SceneNodeModificationTask* tiltRight(Angle amount);
			SceneNodeModificationTask* tiltRight(Angle amount, const SceneNode* viewPoint);
			SceneNodeModificationTask* setDirection(Vector3 direction, bool keepTilt = true);
			SceneNodeModificationTask* lookAt(const SceneNode* target, bool keepTilt = true);

			// Scale
			SceneNodeModificationTask* setScale(Real scalar);
			SceneNodeModificationTask* setScale(Real xScale, Real yScale, Real zScale);
			SceneNodeModificationTask* setScale(const Vector3& scale);
			SceneNodeModificationTask* scale(Real scalar);
			SceneNodeModificationTask* scale(Real xScale, Real yScale, Real zScale);
			SceneNodeModificationTask* scale(const Vector3& scale);

		private:

			class Operation
			{

				public:
					virtual ~Operation() {}
					virtual void apply(SceneNode* node) const = 0;
					virtual void prepare(float amount) = 0;

			};

			class AbsoluteMovement : public Operation
			{

				public:
					AbsoluteMovement(Vector3 vector) : vector(vector) {}

					void apply(SceneNode* node) const {node->move(preparedVector);}
					void prepare(float amount) {preparedVector = vector * amount;}

				private:
					Vector3 vector;
					Vector3 preparedVector;

			};

			class RelativeMovement : public Operation
			{

				public:
					RelativeMovement(Vector3 vector);

					void apply(SceneNode* node) const {node->move(preparedVector);};
					void prepare(float amount) {preparedVector = vector * amount;}

				private:
					Vector3 vector;
					Vector3 preparedVector;

			};

			class ContextRotation : public Operation
			{

				public:
					ContextRotation(Angle angle, Vector3 axis, const SceneNode* context) : angle(angle), axis(axis), context(context) {};

					void apply(SceneNode* node) const {node->rotate(preparedRotation, context);};
					void prepare(float amount) {preparedRotation = Quaternion(angle * amount, axis);}

				private:
					Angle angle;
					Vector3 axis;
					const SceneNode* context;
					Quaternion preparedRotation;

			};

			class Rotation : public Operation
			{

				public:
					Rotation(Angle angle, Vector3 axis) : angle(angle), axis(axis) {};

					void apply(SceneNode* node) const {node->rotate(preparedRotation);};
					void prepare(float amount) {preparedRotation = Quaternion(angle * amount, axis);}

				private:
					Angle angle;
					Vector3 axis;
					Quaternion preparedRotation;

			};

			SceneNodeModificationTask();

			std::list<SceneNode*> models;
			std::list<Operation*> operations;

	};

	inline
	SceneNodeModificationTask::~SceneNodeModificationTask()
	{
		for (auto operation = operations.begin(); operation != operations.end(); operation++)
		{
			delete *operation;
		}
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::create()
	{
		return new SceneNodeModificationTask();
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::create(SceneNode* node)
	{
		return create()->registerNode(node);
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::registerNode(SceneNode* node)
	{
		models.push_back(node);
		return this;
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::unregisterNode(SceneNode* node)
	{
		models.remove(node);
		return this;
	}

	inline
	SceneNodeModificationTask::SceneNodeModificationTask()
	{}

	inline void
	SceneNodeModificationTask::perform()
	{
		for (auto node = models.begin(); node != models.end(); node++)
		{
			for (auto operation = operations.begin(); operation != operations.end(); operation++)
			{
				(*operation)->prepare(MainTaskGroup::get()->timeSinceLastCycle());
				(*operation)->apply(*node);
			}
		}
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::move(Real x, Real y, Real z)
	{
		return move(Vector3(x, y, z));
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::move(const Vector3& vector)
	{
		operations.push_back(new AbsoluteMovement(vector));
		return this;
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::move(const Vector3& vector, Real amount)
	{
		return move(vector * amount);
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::moveLeft(Real amount)
	{
		operations.push_back(new RelativeMovement(CoordinateSystem::get().getLeftVector() * amount));
		return this;
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::moveRight(Real amount)
	{
		operations.push_back(new RelativeMovement(CoordinateSystem::get().getRightVector() * amount));
		return this;
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::moveUp(Real amount)
	{
		operations.push_back(new RelativeMovement(CoordinateSystem::get().getUpVector() * amount));
		return this;
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::moveDown(Real amount)
	{
		operations.push_back(new RelativeMovement(CoordinateSystem::get().getDownVector() * amount));
		return this;
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::moveForward(Real amount)
	{
		operations.push_back(new RelativeMovement(CoordinateSystem::get().getForwardVector() * amount));
		return this;
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::moveBackward(Real amount)
	{
		operations.push_back(new RelativeMovement(CoordinateSystem::get().getBackwardVector() * amount));
		return this;
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::rotate(Angle angle, Vector3 axis)
	{
		operations.push_back(new Rotation(angle, axis));
		return this;
	}

	inline SceneNodeModificationTask*
	SceneNodeModificationTask::rotate(Angle angle, Vector3 axis, const SceneNode* viewPoint)
	{
		operations.push_back(new ContextRotation(angle, axis, viewPoint));
		return this;
	}

}

#endif /* PURGE_MODELMODIFICATIONTASK_H */

