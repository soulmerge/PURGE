#ifndef CLASSES_H
#define CLASSES_H 1

#include <iostream>
#include <memory>
#include <assert.h>

namespace PURGE
{

	// Math

	class Angle;
	class Degree;
	class Radian;
	class Vector3;
	class Quaternion;

	// Space

	class SceneNode;
	typedef SceneNode ObjectGroup;

	// Graphics

	class Renderer;

	class Model;
	class ModelNode;
	class ModelDefinition;

	class Camera;
	class CameraNode;
	class CameraDefinition;

	class Window;

	class Color;

	class Light;
	class AmbientLight;

	class SpotLight;
	class SpotLightNode;
	class SpotLightDefinition;

	class PointLight;
	class PointLightNode;
	class PointLightDefinition;

	class DirectionalLight;
	class DirectionalLightNode;
	class DirectionalLightDefinition;

	// Loop
	
	class Task;
	class TaskGroup;
	class MainTaskGroup;
	class RenderingStartTask;
	class RenderingFinishTask;
	class FpsPrintTask;
	class SceneNodeModificationTask;

}

#endif /* CLASSES_H */

