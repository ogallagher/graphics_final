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

float Obstacle::color[3] = {0.8,0.8,0.8};

Obstacle::Obstacle(int x, int y, int w, int h, int d) {
	location.x = x;
	location.y = y;
	location.z = h/2;
	
	dims[3] = {w,h,d};
}

void Obstacle::display() {
	glPushMatrix();
	
	glTranslatef(location.x,location.y,location.z);
	glColor3f(color[0],color[1],color[2]);
	glutSolidCube(dims[0],dims[1],dims[2]);
	
	glPopMatrix();
}