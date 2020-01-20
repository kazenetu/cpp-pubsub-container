#!/bin/make

# build directory
SRCPATH := ./src

BUILDPATH := ./build
LIBPATH := ./lib
LIBNAME := libpubsub.a

CXX := g++
INCLUDE := -I /usr/local/include -I /usr/include -I./include
CXXFLAGS := -Wall -O2 
LDFLAGS := -L /usr/lib -L /usr/local/lib 
SRCS := $(shell find $(SRCPATH) -name '*.cpp')
OBJS :=  $(patsubst $(SRCPATH)/%,$(BUILDPATH)/%,$(SRCS:.cpp=.o))

$(LIBPATH)/$(LIBNAME):$(OBJS)
	mkdir -p $(LIBPATH)
	ar rcs $@ $(OBJS)

$(BUILDPATH)/%.o : $(SRCPATH)/%.cpp
	mkdir -p  $(BUILDPATH)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS)-o $@ -c $^
