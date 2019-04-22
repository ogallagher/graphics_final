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

//local headers
#include "ovector.h"
class Camera; //don't include camera.h here to avoid circular dependency

//namespaces
using namespace std;

#ifdef __APPLE__

#define GL_SILENCE_DEPRECATION //Mac opengl
#include <GLUT/glut.h>

#else

#include <GL/glut.h> //Windows opengl

#endif

class World {
public:
	static const int EYE_NEAR;
	static float pmatrix[16]; //projection
	static float mvmatrix[16]; //modelview
	static float pmvmatrix[16]; //projection * modelview
	static float umatrix[16]; //2d->3d unprojection
	
	static int dimsWindow[3];
	static double speed; //determines time slow-down and speed-up in the game
	static int dims[3]; //eastwest,northsouth,updown
	static float mouse[2]; //window coords: [-1,1]
	static ovector pointer; //normalized ray camera-to-mouse
	static ovector cursor; //intersection of pointer with ground plane
	static bool clicked;
	static bool keyW, keyD, keyS, keyA;

	static void loadOSSpeed(int);
	static void display();
	static string describe();
	static void loadCamera(); //calls gluLookAt()
	static void updateMouse(int,int);
	static void updateCursor();
	static void drawCursor();

	static Camera *camera;
};

#endif