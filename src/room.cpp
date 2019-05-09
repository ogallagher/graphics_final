/*

Owen Gallagher, Brian Park
6 May 2019

room.cpp

*/

//local includes
#include "../include/room.h"
#include "../include/obstacle.h"

const int Room::DIM_MAX = World::dims[0] + Obstacle::DIM_MIN;
const int Room::WALLS = 2;
const int Room::WALL_DIM_MAX = World::dims[0];
const int Room::PILLARS = 4;
const int Room::PILLAR_DIM_MAX = Obstacle::DIM_MIN*4;
const int Room::BARRIERS = 4;

void Room::display(int rx, int ry) {	
	this->rx = rx*DIM_MAX;
	this->ry = ry*DIM_MAX;
			
	World::loadMaterial(&Obstacle::material);
	for (oit = obstacles.begin(); oit != obstacles.end(); oit++) {
		(*oit)->display();			
	}
	
	Enemy *e;
	for (eit = enemies.begin(); eit != enemies.end(); eit++) {
		e = *eit;
		e->followControl();
		e->shootControl();
		if (e->collideBounds() || e->collideObstacles(&World::obstacles)) {
			e->stay();
		}
		else {
			e->move();
		}
		e->display();			
	}	
}