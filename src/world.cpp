/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

world.cpp

*/

#include "../include/world.h"
#include "../include/camera.h"

double World::speed = 1;
int World::dims[3] = {200,200,100};
int World::mouse[2] = {0,0};
bool World::clicked = false;
bool World::keyW = false;
bool World::keyD = false;
bool World::keyS = false;
bool World::keyA = false;
Camera *World::camera = new Camera();

void World::loadOSSpeed(int osSpeed) {
	speed *= osSpeed;
}

void World::display() {
	cout << "World::display()" << endl;
}

string World::describe() {
	string description = "World: [" 
						+ to_string(dims[0]) + "," 
						+ to_string(dims[1]) + ","
						+ to_string(dims[2]) + "] speed="
						+ to_string(speed);
	
	return description;
}

void World::placeCamera() {
	gluLookAt(camera->location.x,camera->location.y,camera->location.z,
			  camera->subject.x,camera->subject.y,camera->subject.z,
			  0,1,0);
}