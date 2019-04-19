/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

*/

#include "../include/person.h"

int Person::dimsHead[3] = {5,5,5};
int Person::dimsTorso[3] = {5,10,5};

void Person::move() {
	ovector v(&velocity);
	v.mult(World::speed);
	location.add(&velocity);
}

void Person::drawHead() {
	glPushMatrix();

	glColor3f(colorHead[0],colorHead[1],colorHead[2]);

	glScalef(dimsHead[0],dimsHead[1],dimsHead[2]);
	glutSolidCube(1);

	glPopMatrix();
}

//TODO draw torso
void Person::drawTorso() {
	
}

void Person::display() {
	glPushMatrix();

	glRotatef(heading,0,1,0);
	glTranslatef(location.x,location.y,location.z);
	
	//TODO draw person
	drawHead();
	

	glPopMatrix();
}