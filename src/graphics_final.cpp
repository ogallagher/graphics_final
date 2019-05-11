/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

Submission for the 3D OpenGL final project.
It's a top-down shooter with SuperHot-like mechanics, where time is faster when the player
moves, and slower when the player stands still.

TODO <stages>: create start, play, and end stages
= Text class
	= displays number chars
	- supports transformations and materials
	- has stroke thickness parameter (as well as bullet)

*/

//core headers
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>	
#include <chrono>
#include <vector>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION //apple glut and opengl
#include <GLUT/glut.h>
#define OS_SPEED 50		//speed if Mac
#else
#include <GL/glut.h> //windows glut and opengl
#define OS_SPEED 1		//speed if Windows
#endif

//local headers
#include "../include/world.h"
#include "../include/person.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/camera.h"
#include "../include/bullet.h"
#include "../include/obstacle.h"
#include "../include/light.h"
#include "../include/material.h"

//namespaces
using namespace std;

//application variables
#define GAME_NAME "Minuteman"
int dimsScreen[2];
#define FOV 60
int idleCount = 0;
chrono::high_resolution_clock::time_point atime;
chrono::high_resolution_clock::time_point btime;
int dtime = 0;
int fpsInterval = 5000;
int fpsIdeal = 60;

Player *player = nullptr;
vector<Bullet*>::iterator bit;
vector<Obstacle*>::iterator oit;
vector<Enemy*>::iterator eit;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	World::tick();
	World::camera->move();
	World::light->move();
	World::display();
	World::updateCursor();
	World::drawCursor();
	
	player->keyControl();
	player->mouseControl();
	player->shootControl();
	player->move();
	player->collideObstacles(&World::obstacles);
	player->display();
	
	World::loadMaterial(&Bullet::material);
	glLineWidth(Bullet::stroke);
	Bullet *bptr = nullptr;
	for (bit=World::bullets.begin(); bit!=World::bullets.end(); /*conditional increment*/) {
		bptr = *bit;
		bptr->move();
		
		if (bptr->collideObstacles(&World::obstacles) || 
			bptr->collideEnemies(&World::enemies)) {
			bit = World::bullets.erase(bit);
			delete bptr;
		}
		else if (bptr->collidePerson(player)) {
			player->die();
			exit(EXIT_SUCCESS);
			bit = World::bullets.erase(bit);
			delete bptr;
		}
		else {
			bptr->display();
			bit++;
		}		
	}
	
	//measure framerate and update World::speed
	idleCount++;
	btime = chrono::high_resolution_clock::now();
	dtime += chrono::duration_cast<chrono::milliseconds>(btime - atime).count();
	atime = btime;
	
	if (dtime >= fpsInterval) {
		float fps = (float)idleCount*1000/dtime;
		float dfps = (fps-fpsIdeal)/fpsIdeal;
		float adfps = abs(dfps);
		if (adfps > 0.05) {
			if (adfps < 0.5) {
				World::speed *= 1-dfps;
				cout << "World::speed = " << World::speed << endl;
			}
			else {
				cout << "fps measurement ignored: " << fps << endl;
			}
		}
		
		dtime = 0;
		idleCount = 0;
	}
	
	glutSwapBuffers();
}

void reshape(int w, int h) {
	World::dimsWindow[0] = w;
	World::dimsWindow[1] = h;
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	if (w<h) {
		glViewport(0, h/2 - w/2, w, w);
		gluPerspective(FOV,1,World::EYE_NEAR,World::dimsFOV[2]);
	}
	else {
		glViewport(0,0,w,h);
		gluPerspective(FOV,(double)w/h,World::EYE_NEAR,World::dimsFOV[2]/2);
	}
	
    glMatrixMode(GL_MODELVIEW);
	
	//reset fps measures
	dtime = 0;
	idleCount = 0;
	atime = chrono::high_resolution_clock::now();
	
	//implicity calls glutPostRedisplay()
}

void keydown (unsigned char key, int x , int y)
{
	if (key == 'w' || key=='W') {
		World::keyW = true;
		World::keyWalk = true;
	}
	else if (key == 'd' || key=='D') {
		World::keyD = true;
		World::keyWalk = true;
	}
	else if (key == 's' || key=='S') {
		World::keyS = true;
		World::keyWalk = true;
	}
	else if (key == 'a' || key=='A') {
		World::keyA = true;
		World::keyWalk = true;
	}
}

void keyup (unsigned char key, int x , int y) {
	if (key == 'w' || key == 'W') {
		World::keyW = false;
	}
	else if (key == 'd' || key == 'D') {
		World::keyD = false;
	}
	else if (key == 's' || key == 'S') {
		World::keyS = false;
	}
	else if (key == 'a' || key == 'A') {
		World::keyA = false;
	}

	if (World::keyW == false && World::keyD == false &&
		World::keyS == false && World::keyA == false) {
			World::keyWalk = false;
	}
}

void mouseclick(int button, int status, int x, int y) {
	if (status == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			World::clicked = true;
			if(player->reload <= 0) {
				World::bullets.push_back(player->shoot());
				player->reload = Player::RELOAD_TIME;
			}
		}
	}
	else if (status == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON) {
			World::clicked = false;
		}
	}
}

void idle() {
	glutPostRedisplay();
}

void initGLUT(int argc, char**argv) {
	//glut window
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(World::dimsWindow[0],World::dimsWindow[1]);
	dimsScreen[0] = glutGet(GLUT_SCREEN_WIDTH);
	dimsScreen[1] = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition(dimsScreen[0]/2 - World::dimsWindow[0]/2, dimsScreen[1]/2 - World::dimsWindow[1]/2);
	glutCreateWindow(GAME_NAME);
	glutSetCursor(GLUT_CURSOR_NONE);
	
	//glut event handlers
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutPassiveMotionFunc(World::updateMouse);
	glutMouseFunc(mouseclick);
	glutIdleFunc(idle);
}

void initGL() {
	//enable depth test
	glEnable(GL_DEPTH_TEST);

	//enable something else with depth?
	glEnable(GL_DEPTH);

	//load universe dimensions
	glViewport(0,0,World::dimsWindow[0],World::dimsWindow[1]);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV,1,World::EYE_NEAR,World::dimsFOV[2]/2);
	glMatrixMode(GL_MODELVIEW);

	//background color
	glClearColor(0.0,0.1,0.1,1);
	
	//lighting
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
}

//program main
int main(int argc, char** argv) {
	cout << "<<" << GAME_NAME << ">>" << endl;
	cout << "Computer Graphics final project: 3D top-down shooter" << endl;
	cout << "Owen Gallagher, Brian Park" << endl;
	
	cout << "init glut" << endl;
	initGLUT(argc,argv);
	cout << "init opengl" << endl;
	initGL();

	cout << "init world" << endl;
	World::loadOSSpeed(OS_SPEED);
	World::init();
	player = World::player;
	
	cout << "init framerate clock" << endl;
	atime = chrono::high_resolution_clock::now();
	 	
	glutMainLoop();
	exit(EXIT_SUCCESS);
}