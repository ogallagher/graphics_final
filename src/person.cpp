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

int Person::dimsHead[3] = {2,2,2};
int Person::dimsTorso[3] = {3,5,3};
int Person::dimsArm[3] = {1,5,1};
int Person::dimsLeg[3] = {1,4,1};
const int Person::NECK_HEIGHT = 1;
float Person::speed = 0.02;

void Person::move() {
	ovector v(&velocity);
	v.mult(World::speed);
	location.add(&v);
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

void Person::drawArmL() {
	glPushMatrix();

	glTranslatef(-dimsTorso[0]/2.0 - dimsArm[0]/2.0,0,0);
	glScalef(dimsArm[0],dimsArm[1],dimsArm[2]);
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::drawArmR() {
	glPushMatrix();
	
	glTranslatef(dimsTorso[0]/2.0 + dimsArm[0]/2.0,0,0);
	glScalef(dimsArm[0],dimsArm[1],dimsArm[2]);
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::drawArms() {
	glColor3f(colorHead[0],colorHead[1],colorHead[2]);
	
	glPushMatrix();
	
	glTranslatef(0,dimsArm[1]/2,0); //align shoulder with neck
	glRotatef(-90,1,0,0); //rotate around shoulder
	glTranslatef(0,-dimsArm[1]/2,0); //shoulder is origin
	
	drawArmL();
	drawArmR();
	
	glPopMatrix();
}

void Person::drawLegL() {
	glPushMatrix();
	
	glTranslatef(-dimsTorso[0]/2 + dimsLeg[0]/2,0,0);
	glScalef(dimsLeg[0],dimsLeg[1],dimsLeg[2]);
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::drawLegR() {
	glPushMatrix();
	
	glTranslatef(dimsTorso[0]/2 - dimsLeg[0]/2,0,0);
	glScalef(dimsLeg[0],dimsLeg[1],dimsLeg[2]);
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::drawLegs() {
	glColor3f(colorHead[0],colorHead[1],colorHead[2]);
	
	glPushMatrix();

	glTranslatef(0,-dimsTorso[1]/2,0); //align hip with bottom of torso
	glRotatef(0,1,0,0); //rotate around hip
	glTranslatef(0,-dimsLeg[1]/2,0); //hip is origin
	
	drawLegL();
	drawLegR();
	
	glPopMatrix();
}

void Person::drawTorso() {
	glPushMatrix();
	
	//inherited transforms
	glTranslatef(0,dimsTorso[1]/2 + dimsLeg[1]/2,0);
	
	//draw children
	drawLegs();
	
	glRotatef(heading+90,0,1,0);
	drawHead();
	drawArms();
	
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
	
	drawTorso();

	glPopMatrix();
}