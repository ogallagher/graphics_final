/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

world.cpp

*/

#include "../include/world.h"
#include "../include/camera.h"
#include "../include/matrixutils.h"
#include "../include/person.h"

int World::dimsWindow[3] = {600,600,600};
double World::speed = 1;
int World::dims[3] = {200,10,200};
float World::mouse[2] = {0,0};
ovector World::pointer;
ovector World::cursor;
bool World::clicked = false;
bool World::keyW = false;
bool World::keyD = false;
bool World::keyS = false;
bool World::keyA = false;
Camera *World::camera = new Camera();

const int World::EYE_NEAR = World::dimsWindow[2]/20;
const int World::CURSOR_HEIGHT = Person::dimsTorso[1];

float World::pmatrix[16],World::mvmatrix[16],World::pmvmatrix[16],World::umatrix[16];

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
	mouse[0] = 2 * x / (float)dimsWindow[0] - 1; //-1 = left, 1 = right
	mouse[1] = 1 - (2 * y / (float)dimsWindow[1]); //-1 = bottom, 1 = top
}

/*
Adapted from lessons on ray tracing and 3d intersection: 
http://antongerdelan.net/opengl/raycasting.html
Anton Gerdelan 2016

And from GLU:
https://www.khronos.org/opengl/wiki/GluProject_and_gluUnProject_code
*/
void World::updateCursor() {
	//pointer in screen coordinates
	pointer.set(mouse[0],mouse[1],-1,1);
	
	//update projection and modelview matrices
	glGetFloatv(GL_PROJECTION_MATRIX,pmatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX,mvmatrix);
	
	//calculate unprojection matrix
	matrixutils::mult(pmatrix,mvmatrix,pmvmatrix);
	matrixutils::invert(pmvmatrix,umatrix);
	
	//unproject 2d mouse to get 3d pointer
	pointer.applyMatrix(umatrix);
	
	//perspective division
	pointer.w = 1/pointer.w;
	pointer.x *= pointer.w;
	pointer.y *= pointer.w;
	pointer.z *= pointer.w;
	
	//convert to normalized ray
	pointer.sub(&(camera->location));
	pointer.norm();
	
	//ground intersection point
	float d = (CURSOR_HEIGHT - camera->location.y) / pointer.y;
	cursor.set(&pointer);
	cursor.mult(d);
	cursor.add(&(camera->location));
}

void World::drawCursor() {
	glPushMatrix();
	
	if (clicked) {
		glColor3f(1,0,0);
	}
	else {
		glColor3f(0,0,1);
	}
	
	glTranslatef(cursor.x,cursor.y,cursor.z);
	glutSolidCube(3);
	
	glPopMatrix();
}