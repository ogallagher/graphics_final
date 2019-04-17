/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

*/

#include "../include/person.h"

int Person::dimsHead[3] = {25,25,25};
int Person::dimsTorso[3] = {25,25,40};

void Person::move() {
	ovector v(&velocity);
	v.mult(World::speed);
	location.add(&velocity);
}

void Person::drawHead() {
	glPushMatrix();

	glColor3f(colorHead[0],colorHead[1],colorHead[2]);

	//glScalef(dimsHead[0],dimsHead[1],dimsHead[2]);
	glutWireCube(100);

	glPopMatrix();
}

void Person::display() {
	cout << "Person::display()" << endl;

	glPushMatrix();

	glRotatef(heading,0,1,0);
	glTranslatef(location.x,location.y,location.z);
	
	//TODO draw person
	drawHead();

	glPopMatrix();
}