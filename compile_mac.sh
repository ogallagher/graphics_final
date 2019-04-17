#!/bin/sh

#compile source to bin/ directory
g++ \
-framework OpenGL \
-framework GLUT \
src/*.cpp \
-o bin/graphics_final_mac

