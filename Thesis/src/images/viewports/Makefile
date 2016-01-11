CC=g++
CFLAGS=-c -Wall -I /usr/include/OGRE/
LDFLAGS=-lOgreMain
SOURCES=viewports.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=viewports

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f viewports Ogre.log ${OBJECTS}
