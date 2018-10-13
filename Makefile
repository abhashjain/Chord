CXX=g++
CFLAGS=-c -Wall -g -std=c++17
LDFLAGS=-lm
HEADER=-I$(PWD)/include -I$(shell pwd)/../include

SOURCES=$(wildcard ./src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

CHORD_MAIN=./src/main.cpp

CHORD_EXECUTABLE=./chord_main

.PHONY: all bin clean

all: bin
bin: $(CHORD_EXECUTABLE)

$(CHORD_EXECUTABLE): $(OBJECTS) 
	$(CXX) -o $@ $(OBJECTS) $(LIBS)

%.o: %.cpp 
	$(CXX) $(CFLAGS) $(HEADER) $< -o $@

clean:
	-rm $(OBJECTS)
	-rm $(CHORD_EXECUTABLE)
