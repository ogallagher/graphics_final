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
#include <vector>
#include <random>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION //Mac opengl
#include <GLUT/glut.h>
#else
#include <GL/glut.h> //Windows opengl
#endif

//local headers
#include "ovector.h"
class Camera; //don't here to avoid circular dependency
class Light;
class Bullet;
class Obstacle;
class Person;
class Enemy;
class Material;

//namespaces
using namespace std;

class World {
private:
	static random_device randomCore;
	static uniform_real_distribution<float> randomizer;
	
public:
	static const int EYE_NEAR;
	static const int CURSOR_HEIGHT;
	
	static float pmatrix[16]; //projection
	static float mvmatrix[16]; //modelview
	static float pmvmatrix[16]; //projection * modelview
	static float umatrix[16]; //2d->3d unprojection
	
	static int dimsWindow[2];
	static int dimsFOV[3];
	static double t; //world clock
	static double speed; //determines time slow-down and speed-up in the game
	static int dims[3]; //eastwest,northsouth,updown
	static float mouse[2]; //window coords: [-1,1]
	static ovector pointer; //normalized ray camera-to-mouse
	static ovector cursor; //intersection of pointer with ground plane
	static bool clicked;
	static bool keyW, keyD, keyS, keyA;
	
	static Camera *camera;
	static Light *light;
	
	static vector<Bullet> bullets;
	static vector<Obstacle> obstacles;
	static vector<Enemy> enemies;

	static void loadOSSpeed(float);
	static void loadCamera(); //calls gluLookAt()
	static void loadLight(int lightId); //calls glLightfv()
	static void loadMaterial(Material *); //calls glMaterialfv
	static void loadObstacles();
	static void loadEnemies();
	static void display(); //renders camera, lighting, obstacles, enemies
	static string describe();
	static void tick();
	static void updateMouse(int,int);
	static void updateCursor();
	static void drawCursor();
	static float getRandom(); //returns random float in range [0,1)
};

#endif