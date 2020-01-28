#!/bin/make

# build directory
SRCPATH := ./src

BUILDPATH := ./build
BINPATH := ./bin
BINNAME := example.out

CXX := g++
INCLUDE := -I /usr/local/include -I /usr/include -I./include -I../pubsub-container/include
CXXFLAGS := -Wall -O2 
LDFLAGS := -L /usr/lib -L /usr/local/lib -L ../pubsub-container/lib
LIBS := -lpubsub
SRCS := $(shell find $(SRCPATH) -name '*.cpp')
OBJS :=  $(patsubst $(SRCPATH)/%,$(BUILDPATH)/%,$(SRCS:.cpp=.o))

$(BINPATH)/$(BINNAME):$(OBJS)
	mkdir -p $(BINPATH)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

$(BUILDPATH)/%.o : $(SRCPATH)/%.cpp
	mkdir -p  $(BUILDPATH)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ -c $^

.PHONY: clean
 
clean:
	rm -rf $(BUILDPATH)
	rm -rf $(BINPATH)