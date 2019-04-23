/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

*/

//global headers
#include <cmath>

//local headers
#include "../include/world.h"
#include "../include/person.h"
#include "../include/bullet.h"

int Person::dimsHead[3] = {3,3,3};
int Person::dimsTorso[3] = {5,10,3};
const int Person::NECK_HEIGHT = 1;
float Person::speed = 1;

void Person::move() {
	ovector v(&velocity);
	v.mult(World::speed);
	location.add(&velocity);
}

Bullet Person::shoot() {
	float bh = heading/180*3.141593;
	
	ovector bl(cos(bh),0,-sin(bh));
	ovector bv(&bl);
	
	bl.mult(dimsTorso[2]/2 + Bullet::dims[2]/2);
	bl.add(&location);
	
	bv.mult(Bullet::speed);
	
	return Bullet(&bl,&bv);
}

void Person::drawHead() {
	glPushMatrix();

	//transforms
	glTranslatef(0,(dimsTorso[1]+dimsHead[1])/2 + NECK_HEIGHT,0);
	glScalef(dimsHead[0],dimsHead[1],dimsHead[2]);
	
	//material properties
	glColor3f(colorHead[0],colorHead[1],colorHead[2]);
	
	//primitive
	glutSolidCube(1);

	glPopMatrix();
}

void Person::drawTorso() {
	glPushMatrix();
	
	//inherited transforms
	glTranslatef(0,dimsTorso[1]/2,0);
	
	//draw children
	drawHead();
	
	//local transforms
	glScalef(dimsTorso[0],dimsTorso[1],dimsTorso[2]);
	
	//material properties
	glColor3f(colorBody[0],colorBody[1],colorBody[2]);
	
	//primitive
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::display() {
	glPushMatrix();

	glTranslatef(location.x,location.y,location.z);
	glRotatef(heading+90,0,1,0);
	
	drawTorso();

	glPopMatrix();
}