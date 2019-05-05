/*

Owen Gallagher, Brian Park
22 April 2019
Computer Graphics

bullet.cpp

*/

//global headers
#include <iostream>
#include <vector>

//local headers
#include "../include/bullet.h"
#include "../include/person.h"
#include "../include/obstacle.h"
#include "../include/world.h"

using namespace std;

int Bullet::dims[3] = {1,1,2};
float Bullet::speed = 0.1;

const int Bullet::HEIGHT = Person::dimsTorso[1];
const int Bullet::INFLUENCE_RADIUS = dims[2]*4;

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

bool Bullet::collidePeople(vector<Person> *people) {
	bool collided = false;
	
	for (vector<Person>::iterator pit=people->begin(); pit!=people->end() && !collided; pit++) {
		collided = collidePerson(&(*pit));
	}
	
	return collided;
}

bool Bullet::collidePerson(Person *person) {
	ovector shot(&location);
	shot.sub(&past);
	
	//TODO intersection with p->location +- p->dims
	return false;
}

bool Bullet::collideObstacles(vector<Obstacle> *obstacles) {
	bool collided = false;
	
	for (vector<Obstacle>::iterator oit=obstacles->begin(); oit!=obstacles->end() && !collided; oit++) {
		collided = collideObstacle(&(*oit));
	}
	
	return collided;
}

bool Bullet::collideObstacle(Obstacle *obstacle) {
	//check influence radius
	ovector d(&(obstacle->location));
	d.sub(&location);
	d.y = 0;
	
	if (d.mag() < INFLUENCE_RADIUS + Obstacle::INFLUENCE_RADIUS) {
		//location of previous frame
		ovector c(&(obstacle->location));
		c.sub(&past);
		c.y = 0;
		
		/* check obvious collision sectors
			 1 | 2 | 3
			---|---|---
			 8 | 0 | 4
			---|---|---
			 7 | 6 | 5
		*/
		int ow = obstacle->dims[0]/2;
		int od = obstacle->dims[2]/2;
		if (d.x > ow) { //now=1,8,7
			if (c.x < ow) { //past=0,2,3,4,5,6
				
			}
			//else, outside left
		}
		else if (d.x < -ow) { //now=3,4,5
			if (c.x > -ow) { //past=0,1,2,6,8,7
				
			}
			//else, outside right
		}
		else { //now=2,0,6
			
		}
		
		dx = abs(d.x) - obstacle->dims[0]/2;
		dz = abs(d.z) - obstacle->dims[2]/2;
	
		//check special collision sectors
	}
	else {
		return false;
	}
}

ostream & operator <<(ostream &os, const Bullet &ob) {
	os << "Bullet(l=" << ob.location << ",v=" << ob.velocity << ')';
	return os;
}