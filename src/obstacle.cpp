/*

Owen Gallagher, Brian Park
24 April 2019
Computer Graphics

obstacle.cpp

*/

//core headers
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION //apple glut and opengl
#include <GLUT/glut.h>
#else
#include <GL/glut.h> //windows glut and opengl
#endif

//local headers
#include "../include/ovector.h"
#include "../include/obstacle.h"
#include "../include/world.h"
#include "../include/person.h"
#include "../include/material.h"

unsigned int Obstacle::nextId = 0;
Material Obstacle::material;
const int Obstacle::DIM_MIN = 10;
const int Obstacle::HEIGHT = Person::dimsTorso[1] * 4;
const int Obstacle::INFLUENCE_RADIUS = World::dimsFOV[0]/8;

Obstacle::Obstacle(int *rx, int *ry, int x, int z, int w, int d) {
	id = nextId++;
	this->rx = rx;
	this->ry = ry;
	
	location.x = x;
	location.z = z;
	location.y = HEIGHT/2;
	
	if (w < INFLUENCE_RADIUS*2) {
		dims[0] = w;
	}
	else {
		dims[0] = INFLUENCE_RADIUS*2;
	}
	dims[1] = HEIGHT;
	if (d < INFLUENCE_RADIUS*2) {
		dims[2] = d;
	}
	else {
		dims[2] = INFLUENCE_RADIUS*2;
	}
}

void Obstacle::display() {
	glPushMatrix();

	//transforms
	glTranslatef(*rx + location.x,location.y,*ry + location.z);
	glScalef(dims[0],dims[1],dims[2]);
	
	//material properties handled by caller
	
	//primitive
	glutSolidCube(1);
	
	glPopMatrix();
}

string Obstacle::describe() {
	string description = "obstacle" + to_string(id) + "[x=" + to_string(location.x)
						+ " y=" + to_string(location.y)
						+ " z=" + to_string(location.x)
						+ " dims=" + to_string(dims[0])
						+ " " + to_string(dims[1]) + " " + to_string(dims[2]) + "]";
	return description;
}