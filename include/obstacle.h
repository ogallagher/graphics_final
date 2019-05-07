/*

Owen Gallagher, Brian Park
24 April 2019
Computer Graphics

obstacle.h

Obstacles in the world are blocks that people and bullets can collide with.
They are placed randomly.

*/

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../include/ovector.h"
#include "../include/material.h"

class Obstacle {
public:
	static Material material;
	static const int DIM_MIN;
	static const int HEIGHT;
	static const int INFLUENCE_RADIUS;
	
	ovector location;
	int dims[3];
	std::string description;
	
	Obstacle(int, int, int, int); //x,y,width,depth
	
	void display();
	std::string describe();
};

#endif