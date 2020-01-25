#!/bin/bash

# build pubsub-container
make clean --directory=../pubsub-container
make --directory=../pubsub-container

# build example
make clean
make

