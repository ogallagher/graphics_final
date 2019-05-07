/*

Owen Gallagher, Brian Park
6 May 2019

room.cpp

*/

//local includes
#include "../include/room.h"
#include "../obstacle.h"

int Room::DIM_MAX = World::dims[0] + Obstacle::DIM_MIN;
int Room::WALLS = 2;
int Room::WALL_DIM_MAX = DIM_MAX * 0.75;
int Room::PILLARS = 4;
int Room::PILLAR_DIM_MAX = Obstacle::DIM_MIN*4;
int Room::BARRIERS = 4;

void Room::display() {
	Obstacle *o;
	for (oit = obstacles.begin(); oit != obstacles.end(); oit++) {
		o = *oit;
		
		o->display();
	}
	
	Enemy *e;
	for (eit = enemies.begin(); eit != enemies.end(); eit++) {
		e = *eit;
		
		e->followControl();
		e->shootControl();
		e->move();
		if (e->collideObstacles(&World::obstacles)) {
			e->stay();
		}
		e->display();
	}
}