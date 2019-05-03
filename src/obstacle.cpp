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

float Obstacle::color[3] = {0.8,0.8,0.8};
const int Obstacle::HEIGHT = Person::dimsTorso[1] * 4;

Obstacle::Obstacle(int x, int z, int w, int d) {
	location.x = x;
	location.z = z;
	location.y = HEIGHT/2;
	
	dims[0] = w;
	dims[1] = HEIGHT;
	dims[2] = d;
}

void Obstacle::display() {
	glPushMatrix();

	//transforms
	glTranslatef(location.x,location.y,location.z);
	glScalef(dims[0],dims[1],dims[2]);
	
	//material
	glColor3f(color[0],color[1],color[2]);
	
	//primitive
	glutSolidCube(1);
	
	glPopMatrix();
}

string Obstacle::toString() {
	string description = "obstacle[x = " + to_string(location.x)
						+ " y = " + to_string(location.y)
						+ " z = " + to_string(location.x)
						+ " dimens = " + to_string(dims[0])
						+ " " + to_string(dims[1]) + " " + to_string(dims[2]) + "]";
	return description;
}