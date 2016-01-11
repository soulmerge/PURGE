cmake_minimum_required(VERSION 2.8)

SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -ansi -pedantic -Wall -Wno-variadic-macros -std=c++0x")

ADD_LIBRARY(PURGE SHARED
	TrackedObject.cpp
	Math/Degree.cpp
	Math/Radian.cpp
	Math/Angle.cpp
	Math/Vector3.cpp
	Math/Quaternion.cpp
	Space/SceneNode.cpp
	Space/FluentSceneNode.cpp
	Space/CoordinateSystem.cpp
	Graphics/Model.cpp
	Graphics/ModelNode.cpp
	Graphics/ModelDefinition.cpp
	Graphics/Camera.cpp
	Graphics/CameraNode.cpp
	Graphics/CameraDefinition.cpp
	Graphics/Window.cpp
	#Graphics/Viewport.cpp
	Graphics/Color.cpp
	Graphics/Light.cpp
	Graphics/AmbientLight.cpp
	Graphics/SpotLight.cpp
	Graphics/SpotLightDefinition.cpp
	Graphics/SpotLightNode.cpp
	Graphics/PointLight.cpp
	Graphics/PointLightDefinition.cpp
	Graphics/PointLightNode.cpp
	Graphics/Renderer.cpp
	Loop/Task.cpp
	Loop/TaskGroup.cpp
	Loop/MainTaskGroup.cpp
	Loop/RenderingStartTask.cpp
	Loop/RenderingFinishTask.cpp
	Loop/FpsPrintTask.cpp
	Loop/SceneNodeModificationTask.cpp
)

INCLUDE_DIRECTORIES("..")

SET(ENV{ADDITIONAL_LIBS} "$ENV{ADDITIONAL_LIBS} SDL boost_filesystem")

