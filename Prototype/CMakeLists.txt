cmake_minimum_required(VERSION 2.8)

PROJECT(PURGE)

SET(PURGE_MAJOR_VERSION 0)
SET(PURGE_MINOR_VERSION 5)
SET(PURGE_PATCH_VERSION 0)

SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -ansi -pedantic -Wall -Wno-variadic-macros -std=c++0x -isystem /opt/panda/include")
SET(CMAKE_MODULE_PATH "CMakeModules;${CMAKE_MODULE_PATH}")
INCLUDE("Createlib")

#SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg")
#SET (CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS_INIT} "-pg"
#     CACHE STRING "Flags used by the linker during the creation of dll's.")
#SET (CMAKE_MODULE_LINKER_FLAGS ${CMAKE_MODULE_LINKER_FLAGS_INIT} "-pg"
#     CACHE STRING "Flags used by the linker during the creation of modules.")

SET(ENV{ADDITIONAL_LIBS} "")
INCLUDE_DIRECTORIES(lib)
add_subdirectory(lib/PURGE)
add_subdirectory(lib/Bridges)

INCLUDE_DIRECTORIES(${OGRE_INCLUDE_BASE}/OGRE /opt/panda/include /usr/include/python2.7)
LINK_DIRECTORIES(/opt/panda/lib)
add_executable (PURGEDemo
	test/TestScene.cpp
	test/TestScene1.cpp
	test/TestScene2.cpp
	test/TestScene3.cpp
	test/TestScene4.cpp
	test/TestScene5.cpp
	test/TestScene6.cpp
	test/TestScene7.cpp
	test/TestScene8.cpp
	test/TestScene81.cpp
	test/TestScene82.cpp
	test/TestScene9.cpp
	test/TestScene10.cpp
	test/TestScene11.cpp
	test/TestScene12.cpp
	test/PositionGenerator.cpp
	main.cpp)


STRING(REGEX MATCHALL "[A-Za-z_-]+" ADDITIONAL_LIBS $ENV{ADDITIONAL_LIBS})
target_link_libraries (PURGEDemo
	PURGE
	osg
	osgDB
	osgViewer
	panda p3framework pandafx pandaexpress p3dtoolconfig p3dtool p3pystub p3direct pandaegg
	pthread
	${ADDITIONAL_LIBS})

ADD_CUSTOM_TARGET(exec ./PURGEDemo Game5 ";" xset r DEPENDS PURGEDemo)
ADD_CUSTOM_TARGET(debug ddd ./PURGEDemo ";" xset r DEPENDS PURGEDemo)

