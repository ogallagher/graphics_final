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
public:
	static double speed; //determines time slow-down and speed-up in the game
	static int dims[3]; //eastwest,northsouth,updown
	static int mouse[2];
	static bool clicked;
	static bool keyW, keyD, keyS, keyA;

	static void loadOSSpeed(int);
	static void display();
	static string describe();
	static void placeCamera(); //calls gluLookAt()

	static Camera *camera;
};

#endif