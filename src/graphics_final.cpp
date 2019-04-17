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

//apple vs windows glut
#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//local headers
#include "../include/world.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/camera.h"

//namespaces
using namespace std;

//application variables
#define GAME_NAME "Graphics Final"
int dimsWindow[] = {600,600,600};
int dimsScreen[3];

void initGL() {
	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,dimsWindow[0],dimsWindow[1]);
	glLoadIdentity();
	//TODO replace glOrtho2D with glPerspective
	gluOrtho2D(0,dimsWindow[0],0,dimsWindow[1]);
	glMatrixMode(GL_MODELVIEW);
}

void display() {
	cout << "GLUT::display()" << endl;
}

void reshape(int w, int h) {
	cout << "GLUT::reshape()" << endl;
	//implicity calls glutPostRedisplay()
}

void initGLUT(int argc, char**argv) {
	//glut window
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	glutInitWindowSize(dimsWindow[0],dimsWindow[1]);
	//TODO get screen size
	//TODO center window
	glutInitWindowPosition(100,100);
	glutCreateWindow(GAME_NAME);
	
	//glut event handlers
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//TODO mouse funcs
	//TODO keyboard down func
	//TODO keyboard up func
}

//program main
int main(int argc, char** argv) {
	cout << "Computer Graphics final project: 3D top-down shooter" << endl;
	cout << "Owen Gallagher, Brian Park" << endl;
	
	cout << "initGLUT()" << endl;
	initGLUT(argc,argv);
	cout << "initGL()" << endl;
	initGL();
	
	World::display();
	cout << World::describe() << endl;
	
	glutMainLoop();
	
	exit(EXIT_SUCCESS);
}