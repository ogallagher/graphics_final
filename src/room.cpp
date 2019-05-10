/*

Owen Gallagher, Brian Park
6 May 2019

room.cpp

*/

//local includes
#include "../include/room.h"
#include "../include/world.h"
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
		
	//obstacles	
	World::loadMaterial(&Obstacle::material);
	for (oit = obstacles.begin(); oit != obstacles.end(); oit++) {
		(*oit)->display();			
	}
	
	//enemies
	Enemy *e;
	bool active = false;
	int rdx = id[0] - World::roomIndex(World::player->roomX);
	int rdy = id[1] - World::roomIndex(World::player->roomY);
	if ( rdx == 0 && rdy == 0 ) {
		active = true;
	}
	for (eit = enemies.begin(); eit != enemies.end(); eit++) {
		e = *eit;
		
		if (active) {
			e->followControl();
			e->shootControl();
			
			if (e->collideBounds() || 
				e->collideObstacles(&obstacles)) {
				e->stay();
			}
			else {
				e->move();
			}
		}
		else {
			e->stay();
		}
		
		e->display();		
	}	
}