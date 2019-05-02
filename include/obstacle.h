/*

Owen Gallagher, Brian Park
24 April 2019
Computer Graphics

obstacle.h

Obstacles in the world are blocks that people and bullets can collide with.
They are placed randomly.

*/

#include "../include/ovector.h"

class Obstacle {
public:
	static float color[3];
	
	ovector location;
	int dims[3];
	
	Obstacle(int, int, int, int, int); //x,y,width,height,depth
	
	void display();
};