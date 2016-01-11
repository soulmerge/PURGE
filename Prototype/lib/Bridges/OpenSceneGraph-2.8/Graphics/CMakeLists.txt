SET(LIBSOURCES "
	OsgModel.cpp
	OsgGraphics.cpp
	OsgViewport.cpp
	OsgWindow.cpp
	OsgCamera.cpp")
SET(DEPENDENCIES "osg osgViewer")
CREATELIB(PURGEGraphics-Osg)

