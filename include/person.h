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

#include <vector>

//local headers
#include "../include/world.h"
#include "../include/ovector.h"
#include "../include/bullet.h"
#include "../include/obstacle.h"
#include "../include/material.h"

class Enemy; //don't include to prevent circular dependency

class Person {
public:
	static int dimsHead[3];
	static int dimsTorso[3];
	static int dimsArm[3];
	static int dimsLeg[3];
	static const int NECK_HEIGHT;
	static float speed;
	static const int INFLUENCE_RADIUS;

	ovector location;
	ovector velocity;
	float heading;
	float headingLegs;
	Material materialHead;
	Material materialBody;

	Person() {
		heading = 0;
		headingLegs = 0;
		
		materialHead.setColor(1,1,1);
		materialHead.setADS(0.25,1,1);
		
		materialBody.setColor(0.25,0.25,0.25);
		materialBody.setADS(0.25,1,0.5);
	};

	void move();
	void display();
	Bullet shoot();

	bool collideObstacles(vector<Obstacle> *);
	bool collidePeople(vector<Person> *);
	bool collidePeople(vector<Enemy> *);
	bool collideObstacle(Obstacle *);
	bool collidePerson(Person *);
	void die();

protected:
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