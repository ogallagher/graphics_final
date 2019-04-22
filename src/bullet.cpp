/*

Owen Gallagher, Brian Park
22 April 2019
Computer Graphics

bullet.cpp

*/

#include "../include/bullet.h"
#include "../include/person.h"
#include "../include/world.h"

const int Bullet::HEIGHT = Person::dimsTorso[1];
int Bullet::dims[3] = {1,1,2};
float Bullet::speed = 1;

void Bullet::display() {
	glPushMatrix();
	
	//transforms
	glTranslatef(location.x,location.y,location.z);
	glRotatef(velocity.headingY()+90,0,1,0);
	
	//material properties
	glColor3f(0,1,0);
	
	//primitive
	glBegin(GL_LINES);
	glVertex3f(0,0,(float)dims[2]/2);
	glVertex3f(0,0,-(float)dims[2]/2);
	glEnd();
	
	glPopMatrix();
}

void Bullet::move() {
	past.set(&location);
	ovector v(&velocity);
	v.mult(World::speed);
	location.add(&v);
}

bool Bullet::collideBounds() {
	if (location.x < -World::dims[0]/2 || location.x > World::dims[0]/2 || 
	location.z < -World::dims[2]/2 || location.z > World::dims[2]/2) {
		return true;
	}
	else {
		return false;
	}
}

bool Bullet::collidePerson(Person *p) {
	ovector shot(&location);
	shot.sub(&past);
	
	//TODO intersection with p->location +- p->dims
	return false;
}

bool Bullet::collideObstacle() {
	//TODO collide with obstacles
	return false;
}