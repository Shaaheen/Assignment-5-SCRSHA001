#Makefile for compiling work
#(C) Benjamin Hugo, 2015
#You are free to modify and reuse this in your own practicals
#This file is in the public domain

CPP=g++
CPPFLAGS=-std=c++11
EXE_NAME=unitTests
#define a generic rule: to go from .cpp to .o files make should invoke the c++ compiler
#the syntax tells make to invoke the compiler without linking (-c), outputting a .o file reading a .cpp file, additionally specifying flags

$(EXE_NAME): AudioUnitTests.o Audio.o
	$(CPP) -o $(EXE_NAME) AudioUnitTests.o Audio.o $(CPPFLAGS) 

Audio.o : ../Audio.h 
	$(CPP) -c -o Audio.o $(CPPFLAGS)

AudioUnitTests.o : ../Audio.h AudioUnitTests.cpp
	$(CPP) -c -o AudioUnitTests.o AudioUnitTests.cpp $(CPPFLAGS)
#Never submit binaries to your git repo or vula, so create a rule for cleaning up the binary objects just leaving your source code behind
clean:
	@rm *.o unitTests