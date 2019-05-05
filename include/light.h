/*

Owen Gallagher, Brian Park
5 May 2019
Computer Graphics

light.h

Class to represent an OpenGL light and its properties.

*/

#ifndef LIGHT_H
#define LIGHT_H

//local includes
#include "../include/ovector.h"
#include "../include/material.h"
#include "../include/obstacle.h"

class Light {
public:
	static const int HEIGHT;
	
	ovector *target;
	ovector location;
	
	Material material;
	
	void loadTarget(ovector *);
	void move();
};

#endif