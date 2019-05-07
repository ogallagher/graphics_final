/*

Owen Gallagher, Brian Park
6 May 2019
Computer Graphics

room.h

*/

#ifndef ROOM_H
#define ROOM_H

//core includes
#include <vector>

//local includes
#include "../include/world.h"
#include "../include/obstacle.h"
#include "../include/enemy.h"

class Room {
private:
	vector<Obstacle *>::iterator oit;
	vector<Enemy *>::iterator eit;
	
public:
	static const int DIM_MAX;
	static const int WALLS;
	static const int WALL_DIM_MAX;
	static const int PILLARS;
	static const int PILLAR_DIM_MAX;
	static const int BARRIERS;
	
	vector<Obstacle *> obstacles;
	vector<Enemy *> enemies;
	
	int index[2];
	int location[2];
	
	Room(int ix, int iy) {
		index[0] = ix;
		index[1] = iy;
		
		location[0] = ix * DIM_MAX;
		location[1] = iy * ;
	};
	
	void update();
};

#endif