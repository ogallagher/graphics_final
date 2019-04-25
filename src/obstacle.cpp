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

float Obstacle::color[3] = {0.8,0.8,0.8};

Obstacle::Obstacle(int x, int y, int w, int h, int d) {
	location.x = x;
	location.y = y;
	location.z = h/2;
	
	dims[0] = w;
	dims[1] = h;
	dims[2] = d;
}

void Obstacle::display() {
	glPushMatrix();
	
	//transforms
	glTranslatef(location.x,location.y,location.z);
	glTranslatef(dims[0],dims[1],dims[2]);
	
	//material
	glColor3f(color[0],color[1],color[2]);
	
	//primitive
	glutSolidCube(1);
	
	glPopMatrix();
}