/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

world.cpp

*/

#include <iostream> //TODO delete

#include "../include/world.h"
#include "../include/camera.h"

int World::dimsWindow[3] = {600,600,600};
double World::speed = 1;
int World::dims[3] = {200,10,200};
float World::mouse[2] = {0,0};
bool World::clicked = false;
bool World::keyW = false;
bool World::keyD = false;
bool World::keyS = false;
bool World::keyA = false;
Camera *World::camera = new Camera();

const int World::MOUSE_OFFSET_Y = 5;

void World::loadOSSpeed(int osSpeed) {
	speed *= osSpeed;
}

void World::display() {
	loadCamera();

	glPushMatrix();
	
	glScalef(World::dims[0],World::dims[1],World::dims[2]);
	glColor3f(1,1,1);
	glutWireCube(1.0);

	glPopMatrix();
}

string World::describe() {
	string description = "World: [" 
						+ to_string(dims[0]) + "," 
						+ to_string(dims[1]) + ","
						+ to_string(dims[2]) + "] speed="
						+ to_string(speed);
	
	return description;
}

void World::loadCamera() {
	gluLookAt(camera->location.x,camera->location.y,camera->location.z,
			  camera->subject.x,camera->subject.y,camera->subject.z,
			  0,1,0);
}

void World::updateMouse(int x, int y) {
	mouse[0] = x / (float)dimsWindow[0]; //0 = left, 1 = right
	mouse[1] = 1 - (y / (float)dimsWindow[1]); //0 = top, 1 = bottom
}

void World::drawMouse() {
	ovector cursor(&(camera->subject));
	
	glPushMatrix();
	
	glTranslatef(cursor.x,cursor.y,cursor.z);
	glScalef(2,2,2);
	
	glColor3f(1,0,0);
	
	glutSolidSphere(1,5,5);
	
	glPopMatrix();
}