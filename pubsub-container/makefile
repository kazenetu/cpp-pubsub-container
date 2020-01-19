#!/bin/make

# build directory
SRCPATH = ./src

BUILDPATH = ./build
LIBPATH = ./lib
LIBNAME = libpubsub.a

CXX = g++
INCLUDE = -I /usr/local/include -I /usr/include -I./include
CXXFLAGS = -Wall -O2 
LDFLAGS = -L /usr/lib -L /usr/local/lib 

$(LIBPATH)/$(LIBNAME):$(OBJS)
	mkdir -p $(LIBPATH)
	ar r $(LIBPATH)/LIBNAME $@

$(BUILDPATH)/%.o : SRCPATH/%.cpp
	mkdir -p  $(BUILDPATH)
    $(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS)-o $(BUILDPATH)/$@ -c $^
