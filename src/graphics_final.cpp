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
#include <chrono>
#include <vector>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION //apple glut and opengl
#include <GLUT/glut.h>
#define OS_SPEED 50		//speed if Mac
#else
#include <GL/glut.h> //windows glut and opengl
#define OS_SPEED 2.5		//speed if Windows
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
#include "../include/text.h"

//namespaces
using namespace std;

//application variables
const string GAME_NAME = "Minuteman";
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

const int INTRO_LEN = 7;
string intro[INTRO_LEN] = {
	"hit enter >",
	"wasd keys to move\nmouse to shoot >",
	"time is faster\nwhen you move >",
	"your score is the number\nof enemies you kill >",
	"if you get hit\nyou die >",
	"you win when there\nare no enemies left >",
	"but i highly\ndoubtyou can get\nthat far"
};
int introProgress = 0;
Text titleText(GAME_NAME, 12, 18);
Text welcomeText(intro[introProgress], 5, 10);
Text startText("begin", 10, 15);
Text scoreText("0", 10, 10);
Text gameoverText("game over", 10, 15);

void setStage(int next) {
	switch (next) {
		case STAGE_START:
		introProgress = 0;
		
		case STAGE_PLAY:
		World::reset();
		player->score = 0;
		scoreText.set("0");
		break;
		
		case STAGE_END:
		//TODO stage end
		break;
		
		default:
		break;
	}
	
	World::stage = next;
}

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
	Bullet *bptr = nullptr;
	for (bit=World::bullets.begin(); bit!=World::bullets.end(); /*conditional increment*/) {
		bptr = *bit;
		bptr->move();
	
		if (bptr->collideObstacles(&World::obstacles)) {
			bit = World::bullets.erase(bit);
			delete bptr;
		}
		else if (bptr->collideEnemies(&World::enemies)) {
			if (bptr->good) {
				scoreText.set(to_string(player->score)); //update score text
			}
			
			bit = World::bullets.erase(bit);
			delete bptr;
		}
		else if (bptr->collidePerson(player)) {
			player->die();
			
			bit = World::bullets.erase(bit);
			delete bptr;
			
			setStage(STAGE_END);
		}
		else {
			bptr->display();
			bit++;
		}		
	}
	
	if (World::stage == STAGE_START) {
		titleText.location.set(&(player->location));
		titleText.location.z -= 15;
		titleText.display();
		
		if (introProgress < INTRO_LEN) {
			welcomeText.location.set(&(player->location));
			welcomeText.location.z += 10;
			welcomeText.display();
		}
		else {
			startText.location.set(&(player->location));
			startText.location.z += 15;
			
			if (startText.selected()) { //checks dist to cursor
				setStage(STAGE_PLAY);
			}
			else {
				startText.display();
			}
		}
	}
	else if (World::stage == STAGE_PLAY) {
		scoreText.location.set(&(player->location));
		scoreText.location.y += 30;
		scoreText.display();
	}
	else if (World::stage == STAGE_END) {
		gameoverText.location.set(&(player->location));
		gameoverText.location.z -= 15;
		gameoverText.display();
		
		scoreText.location.set(&(player->location));
		scoreText.location.y += 30;
		scoreText.display();
		
		startText.location.set(&(player->location));
		startText.location.z += 15;
		
		if (startText.selected()) {
			setStage(STAGE_PLAY);
		}
		else {
			startText.display();
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

void keydown(unsigned char key, int x , int y) {
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
	else if (key == '\n' || key == '\r') {
		if (World::stage == STAGE_START) {
			if (introProgress < INTRO_LEN-1) {
				welcomeText.set(intro[++introProgress]);
			}
			else {
				introProgress = INTRO_LEN;
			}
		}
	}
}

void keyup(unsigned char key, int x , int y) {
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
	glutCreateWindow(GAME_NAME.c_str());
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
	
	//stroke width
	glLineWidth(2);
	
	//lighting
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
}

//program main
int main(int argc, char** argv) {
	cout << "<-- " << GAME_NAME << " -->" << endl;
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
	
	cout << "init text" << endl;
	titleText.material.setColor(0.4,0,1);
	
	startText.material.setColor(0.3,1,0.2);
	startText.materialHovered.setColor(1,1,1);
	
	gameoverText.material.setColor(1,0,0);
	
	scoreText.horizontal = false;
	scoreText.material.setColor(0.8,0.7,0);
		
	setStage(STAGE_START);
	
	cout << "init framerate clock" << endl;
	atime = chrono::high_resolution_clock::now();
	 	
	glutMainLoop();
	exit(EXIT_SUCCESS);
}