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

#if defined(__APPLE__)

#define GL_SILENCE_DEPRECATION //Mac opengl
#include <GLUT/glut.h>

#else

#include <GL/glut.h> //Windows opengl

#endif

class World {
private:
	static const int MOUSE_OFFSET_Y;
	
public:
	static const int PROJECT_PLANE_OFFSET_Z;
	static float pmatrix[16];
	static float ipmatrix[16];
	static float mvmatrix[16];
	static float imvmatrix[16];
	
	static int dimsWindow[3];
	static double speed; //determines time slow-down and speed-up in the game
	static int dims[3]; //eastwest,northsouth,updown
	static float mouse[2];
	static ovector cursor;
	static bool clicked;
	static bool keyW, keyD, keyS, keyA;

	static void loadOSSpeed(int);
	static void loadPMatrix();
	static void display();
	static string describe();
	static void loadCamera(); //calls gluLookAt()
	static void updateMouse(int,int);
	static void updateCursor();
	static void drawCursor();
	static bool invertMatrix(const float [16], float [16]);

	static Camera *camera;
};

#endif