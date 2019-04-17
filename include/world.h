/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

world.h

*/

#ifndef WORLD_H
#define WORLD_H

//core headers
#include <iostream>
#include <string>

//namespaces
using namespace std;

int osSpeed = 1;		//if Windows
#if defined(__APPLE__)
#define osSpeed 15		//if Mac, override other osSpeed
#endif

class World {
public:
	static double speed; //determines time slow-down and speed-up in the game
	static int dims[3]; //eastwest,northsouth,updown
	static void display();
	static string describe();
};

double World::speed = 1*osSpeed;
int World::dims[3] = {200,200,100};

void World::display() {
	cout << "World::display()" << endl;
}

string World::describe() {
	string description = "World: [" 
						+ to_string(dims[0]) + "," 
						+ to_string(dims[1]) + ","
						+ to_string(dims[2]) + "] speed="
						+ to_string(speed) + " osspeed=" 
						+ to_string(osSpeed);
	
	return description;
}

#endif