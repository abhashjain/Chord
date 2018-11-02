#
#
# Author : Abhash Jain (ajain28) - CSC591 - HW2
# Make File to build the Project
# debug image option is also available Do: make debug for debug messages
#
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
	chmod 777 chord
	sudo cp -pf chord /usr/bin/chord
	sudo cp -pf chord_main /usr/bin/chord_main

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
