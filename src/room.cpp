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
			(*oit)->display();			
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
	
	printf("destroying obstacles...\n");
	bool go = true;
	oit = obstacles.end()-1;
	while (go) {
		(*oit)->destroy();
		oit = obstacles.erase(oit);
		
		if (oit == obstacles.begin()) {
			(*oit)->destroy();
			obstacles.erase(oit);
			go = false;
		}
	}
	
	printf("destroying enemies...\n");
	go = true;
	eit = enemies.end()-1;
	while (go) {
		(*eit)->die(false,-1,-1);
		eit = enemies.erase(eit);
		
		if (eit == enemies.begin()) {
			(*eit)->die(false,-1,-1); //die as if from another enemy. room erase handled.
			enemies.erase(eit);
			go = false;
		}
	}
}