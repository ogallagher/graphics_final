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
	static unsigned int nextId;
	
	static Material material;
	static const int DIM_MIN;
	static const int HEIGHT;
	static const int INFLUENCE_RADIUS;
	
	unsigned int id;
	ovector location;
	int dims[3];
	int *rx; //pointers to room locations
	int *ry;
	
	Obstacle(int *rx, int *ry, int x, int z, int w, int d);
	
	void display();
	std::string describe();
};

#endif