CC=g++
CFLAGS=-c -Wall -I /usr/include/OGRE/
LDFLAGS=-lOgreMain
SOURCES=camera.cpp sphinx/archives/Geometrik/Geodesic.cpp sphinx/archives/Geometrik/GeometricMesh.cpp sphinx/archives/Geometrik/Mesh_Cube.cpp sphinx/archives/Geometrik/Mesh_GeoEllipse.cpp sphinx/archives/Geometrik/Mesh_Geosphere.cpp sphinx/archives/Geometrik/Mesh_Icosa.cpp sphinx/archives/Geometrik/Mesh_parabola.cpp sphinx/archives/Geometrik/Mesh_Sphere.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=camera

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) sphinx/archives/Geometrik/macros.h
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f camera Ogre.log ${OBJECTS}
