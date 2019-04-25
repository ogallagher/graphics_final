/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics 

person.h

Superclass for all people in the game (player, enemies)

*/

#ifndef PERSON_H
#define PERSON_H

//core headers
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//local headers
#include "../include/world.h"
#include "../include/ovector.h"
#include "../include/bullet.h"

class Person {
public:
	static int dimsHead[3];
	static int dimsTorso[3];
	static int dimsArm[3];
	static int dimsLeg[3];
	static const int NECK_HEIGHT;
	static float speed;

	ovector location;
	ovector velocity;
	float heading;
	float colorHead[3];
	float colorBody[3];

	Person() {
		heading = 0;

		colorHead[0] = 1;//0.75;
		colorHead[1] = 1;//0.75;
		colorHead[2] = 1;//0.75;

		colorBody[0] = 0.25;
		colorBody[1] = 0.25;
		colorBody[2] = 0.25;
	};
	void move();
	void display();
	Bullet shoot();

protected:
	//TODO draw parts of the body
	void drawHead();
	void drawTorso();
	void drawArmL();
	void drawArmR();
	void drawArms();
	void drawLegL();
	void drawLegR();
	void drawLegs();
};

#endif