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
const int Room::WALL_DIM_MAX = DIM_MAX * 0.75;
const int Room::PILLARS = 4;
const int Room::PILLAR_DIM_MAX = Obstacle::DIM_MIN*4;
const int Room::BARRIERS = 4;

void Room::display() {
	if (!ghost) {		
		World::loadMaterial(&Obstacle::material);
		
		for (oit = obstacles.begin(); oit != obstacles.end(); oit++) {
			Obstacle o = **oit;
		
			o.display();			
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
}

void Room::destroy() {
	ghost = true;
	obstacles.clear();
	enemies.clear();
}