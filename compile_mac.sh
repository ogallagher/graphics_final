#!/bin/sh

#compile source to bin/mac/ directory
g++ \
-framework OpenGL \
-framework GLUT \
src/*.cpp \
-o bin/mac/graphics_final_mac
