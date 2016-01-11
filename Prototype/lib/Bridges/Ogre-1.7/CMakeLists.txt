FIND_PATH(OGRE_INCLUDE_BASE OGRE/Ogre.h)
INCLUDE_DIRECTORIES(${OGRE_INCLUDE_BASE}/OGRE)

SET(LIBSOURCES "
	Transcription.cpp
	OgreWindow.cpp
	OgreSceneNode.cpp
	OgreRenderer.cpp
	OgreModel.cpp
	OgreCamera.cpp
	OgreSpotLight.cpp
	OgrePointLight.cpp
	sphinx/archives/Geometrik/macros.h
	sphinx/archives/Geometrik/Geodesic.cpp
	sphinx/archives/Geometrik/GeometricMesh.cpp
	sphinx/archives/Geometrik/Mesh_Cube.cpp
	sphinx/archives/Geometrik/Mesh_GeoEllipse.cpp
	sphinx/archives/Geometrik/Mesh_Geosphere.cpp
	sphinx/archives/Geometrik/Mesh_Icosa.cpp
	sphinx/archives/Geometrik/Mesh_parabola.cpp
	sphinx/archives/Geometrik/Mesh_Sphere.cpp
	")

SET(DEPENDENCIES "OgreMain OIS boost_filesystem")
CREATELIB("PURGEGraphics-Ogre")

