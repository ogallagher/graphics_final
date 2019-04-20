/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

*/

#include "../include/person.h"

int Person::dimsHead[3] = {5,5,5};
int Person::dimsTorso[3] = {3,10,3};
const int Person::NECK_HEIGHT = 1;

void Person::move() {
	ovector v(&velocity);
	v.mult(World::speed);
	location.add(&velocity);
}

void Person::drawHead() {
	glPushMatrix();

	//transforms
	glTranslatef(0,(dimsTorso[1]+dimsHead[1])/2 + NECK_HEIGHT,0);
	glScalef(dimsHead[0],dimsHead[1],dimsHead[2]);
	
	//material properties
	glColor3f(colorHead[0],colorHead[1],colorHead[2]);
	
	//base shape
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
	
	//base shape
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::display() {
	glPushMatrix();

	glRotatef(heading,0,1,0);
	glTranslatef(location.x,location.y,location.z);
	
	drawTorso();

	glPopMatrix();
}