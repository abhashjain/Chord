CXX=g++
CFLAGS=-c -Wall -g -std=c++17
LDFLAGS=-lm
HEADER=-I$(PWD)/include -I$(shell pwd)/../include

SOURCES=$(wildcard ./src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEBUG_OBJECTS=$(SOURCES:.cpp=.d.o)

CHORD_MAIN=./src/main.cpp

CHORD_EXECUTABLE=./chord_main
DEBUG_EXE=./debug_chord

.PHONY: all bin clean debug dclean

all: bin
bin: $(CHORD_EXECUTABLE)

$(CHORD_EXECUTABLE): $(OBJECTS) 
	$(CXX) -o $@ $(OBJECTS) $(LIBS)

%.o: %.cpp 
	$(CXX) $(CFLAGS) $(HEADER) $< -o $@

clean:
	-rm $(OBJECTS)
	-rm $(CHORD_EXECUTABLE)

debug: $(DEBUG_EXE)

$(DEBUG_EXE): $(DEBUG_OBJECTS)
	$(CXX) -o $@ $(DEBUG_OBJECTS) $(LIBS) -DDEBUG_ENABLE

%.d.o: %.cpp
	$(CXX) $(CFLAGS) $(HEADER) $< -o $@ -DDEBUG_ENABLE

dclean:
	-rm $(DEBUG_OBJECTS)
	-rm $(DEBUG_EXE)