CC=g++
CFLAGS=-O0 -ggdb -Wno-variadic-macros -std=c++0x -c -Wall -I /usr/include/python2.7 -isystem /opt/panda/include

LDFLAGS=-L /opt/panda/lib/ -l panda -l p3framework -l pandafx -l pandaexpress -l p3dtoolconfig -l p3dtool -l p3pystub -l p3direct -l pandaegg -l pthread -Wl,-rpath,/opt/panda/lib
SOURCES=panda.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=panda

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f panda ${OBJECTS}
