/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

Submission for the 3D OpenGL final project.
It's a top-down shooter with SuperHot-like mechanics, where time is faster when the player
moves, and slower when the player stands still.

TODO <master>
- enemy
	- point at player method
- player
	+ move for arrow keys
	+ rotate upper body towards cursor
	- score variable
	- variables for shooting (ammo, reload time)
- bullet class
	- collision with: person, obstacle
	+ collision with world bounds
- obstacle class
- person
	+ shoot method
	- die method
	- walking animation
+ world/app
	+ modify World::speed based on framerate
	+ track cursor in 2d
	+ cursor-world projection: draw a ray representing the current mouse position
- research/questions
	- how to use sound with opengl/glut (so we could have sound effects)
	- how should we set up the environment?
	- how should we spawn enemies?
	- how should the enemies behave (how they follow the player and shoot)?

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
#define osSpeed 50		//speed if Mac

#else

#include <GL/glut.h> //windows glut and opengl
#define osSpeed 1		//speed if Windows

#endif

//local headers
#include "../include/world.h"
#include "../include/person.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/camera.h"
#include "../include/bullet.h"

//namespaces
using namespace std;

//application variables
#define GAME_NAME "Graphics Final"
int dimsScreen[2];
#define FOV 60
double t = 0;
int idleCount = 0;
chrono::high_resolution_clock::time_point atime;
chrono::high_resolution_clock::time_point btime;
int dtime = 0;
int fpsInterval = 5000;
int fpsIdeal = 60;

Player player;
vector<Bullet> bullets;
int bulletsLen = 0;
Bullet *bullet = nullptr;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	t += 0.001*World::speed;
	World::camera->location.set(World::dims[0]/8,sin(t)*World::dimsUniverse[1]/16 + World::dimsUniverse[1]/4,World::dims[2]/2);
	World::display();
	
	World::updateCursor();
	World::drawCursor();
	
	player.keyControl();
	player.mouseControl();
	player.move();
	player.display();
	
	for (unsigned int i=0; i<bulletsLen; i++) {
		bullet = &bullets[i];
		
		if (bullet->collideBounds()) {
			bullets.erase(bullets.begin()+i);
			i--;
			bulletsLen--;
		}
		else {
			bullet->move();
			bullet->display();
		}
	}
	
	glutSwapBuffers();
	
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
}

void reshape(int w, int h) {
	World::dimsWindow[0] = w;
	World::dimsWindow[1] = h;
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	if (w<h) {
		glViewport(0, h/2 - w/2, w, w);
		gluPerspective(FOV,1,World::EYE_NEAR,World::dimsUniverse[2]);
	}
	else {
		glViewport(0,0,w,h);
		gluPerspective(FOV,(double)w/h,World::EYE_NEAR,World::dimsUniverse[2]/2);
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

void mouseclick(int button, int status, int x, int y) {
	if (status == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			World::clicked = true;
			
			//TODO player.shoot()
			Bullet bullet = player.shoot();
			bullets.push_back(bullet);
			bulletsLen++;
			cout << "Player shot: " << bullet << endl;
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
	gluPerspective(FOV,1,World::EYE_NEAR,World::dimsUniverse[2]/2);
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

	cout << "init player..." << endl;
	player.location.set(0,0,0);

	cout << "init camera..." << endl;
	World::camera->location.set(World::dims[0]/8,World::dimsUniverse[0]/2,World::dims[2]/2);
	World::camera->subject.set(&(player.location));
	
	cout << "init framerate clock..." << endl;
	atime = chrono::high_resolution_clock::now();
	 	
	glutMainLoop();
	
	exit(EXIT_SUCCESS);
}