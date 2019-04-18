/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

Submission for the 3D OpenGL final project.
It's a top-down shooter with SuperHot-like mechanics, where time is faster when the player
moves, and slower when the player stands still.

*/

//core headers
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>

int osSpeed = 1;		//speed if Windows

//apple vs windows glut and opengl
#if defined(__APPLE__)

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#define osSpeed 15		//if Mac, override other osSpeed

#else

#include <GL/glut.h>

#endif

//local headers
#include "../include/world.h"
#include "../include/person.h"
//#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/camera.h"

//namespaces
using namespace std;

//application variables
#define GAME_NAME "Graphics Final"
int dimsWindow[] = {600,600,600};
int dimsScreen[2];
#define FOV 60
Person person;
double t=0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//TODO delete this (it's for testing the universe dimensions and camera setup)
	glPushMatrix();
	
	glTranslatef(100*cos(t),100*sin(t),100*sin(0.7*t));
	glRotatef(15*t,1,0,0);
	glRotatef(12*t,0,1,0);
	glRotatef(9*t,0,0,1);
	glScalef(1,3,1);
	glutWireCube(100);
	glPopMatrix();

	//person.display();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	cout << "GLUT::reshape()" << endl;
	//implicity calls glutPostRedisplay()
}

void keydown (unsigned char key, int x , int y)
{
	if (key == 'w') {
		World::keyW = true;
	}
	else if (key == 'd') {
		World::keyD = true;
	}
	else if (key == 's') {
		World::keyS = true;
	}
	else if (key == 'a') {
		World::keyA = true;
	}
}

void keyup (unsigned char key, int x , int y) {
	if (key == 'w') {
		World::keyW = false;
	}
	else if (key == 'd') {
		World::keyD = false;
	}
	else if (key == 's') {
		World::keyS = false;
	}
	else if (key == 'a') {
		World::keyA = false;
	}
}

void mousemove(int x, int y) {
	World::mouse[0] = x / (float)dimsWindow[0]; //0 = left, 1 = right
	World::mouse[1] = 1 - (y / (float)dimsWindow[1]); //0 = top, 1 = bottom
}

void mouseclick(int button, int status, int x, int y) {
	if (status == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			cout << "mouse.leftButton" << endl;
			World::clicked = true;
		}
	}
	else if (status == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON) {
			World::clicked = false;
		}
	}
}

void idle() {
	t += 0.01*osSpeed;
	glutPostRedisplay();
}

void initGLUT(int argc, char**argv) {
	//glut window
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(dimsWindow[0],dimsWindow[1]);
	dimsScreen[0] = glutGet(GLUT_SCREEN_WIDTH);
	dimsScreen[1] = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition(dimsScreen[0]/2 - dimsWindow[0]/2, dimsScreen[1]/2 - dimsWindow[1]/2);
	glutCreateWindow(GAME_NAME);
	
	//glut event handlers
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutPassiveMotionFunc(mousemove);
	glutMouseFunc(mouseclick);
	glutIdleFunc(idle);
}

void initGL() {
	//enable depth test
	glEnable(GL_DEPTH_TEST);

	//load universe dimensions
	glViewport(0,0,dimsWindow[0],dimsWindow[1]);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(FOV,1,dimsWindow[2]/2,-dimsWindow[2]/2);
	glOrtho(-dimsWindow[0]/2,dimsWindow[0]/2,-dimsWindow[1]/2,dimsWindow[1]/2,dimsWindow[2]/2,-dimsWindow[2]/2);
	glMatrixMode(GL_MODELVIEW);

	//background color
	glClearColor(0.2,0,0.1,1);

	//stroke thickness
	glLineWidth(2);
}

//program main
int main(int argc, char** argv) {
	cout << "Computer Graphics final project: 3D top-down shooter" << endl;
	cout << "Owen Gallagher, Brian Park" << endl;
	
	cout << "initGLUT()..." << endl;
	initGLUT(argc,argv);
	cout << "initGL()..." << endl;
	initGL();

	cout << "init World..." << endl;
	World::loadOSSpeed(osSpeed);
	cout << World::describe() << endl;

	cout << "init person..." << endl;
	person.location.set(0,0,0);

	cout << "init camera..." << endl;
	World::camera->location.set(0,0,0.8*dimsWindow[2]/2);
	World::camera->subject.set(&(person.location));
	World::placeCamera();
	
	glutMainLoop();
	
	exit(EXIT_SUCCESS);
}