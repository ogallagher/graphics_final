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
#include "../include/enemy.h"
#include "../include/obstacle.h"
#include "../include/world.h"
#include "../include/material.h"
#include "../include/player.h"

using namespace std;

int Bullet::dims[3] = {1,1,2};
float Bullet::speed = 0.1;
Material Bullet::material;

const int Bullet::HEIGHT = Person::dimsTorso[1];
const int Bullet::INFLUENCE_RADIUS = dims[2]*4;

void Bullet::display() {
	glPushMatrix();
	
	//transforms
	glTranslatef(location.x,location.y,location.z);
	glRotatef(velocity.headingY()+90,0,1,0);
	
	//material properties handled by caller
	
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

bool Bullet::collideEnemies(vector<Enemy> *enemies) {
	bool collided = false;
	
	for (vector<Enemy>::iterator eit=enemies->begin(); eit!=enemies->end() && !collided; eit++) {
		collided = collidePerson(static_cast<Person*>(&(*eit)));
		if(collided) {
			eit->die(good);
		}
	}
	
	return collided;
}

bool Bullet::collidePerson(Person *person) {
	//check influence radius
	ovector d(&(person->location));
	d.x += *(person->rx);
	d.z += *(person->ry);
	d.sub(&location);
	d.y = 0;
	
	if (d.mag() < INFLUENCE_RADIUS + Person::INFLUENCE_RADIUS) {
		//location of previous frame
		ovector c(&(person->location));
		d.x += *(person->rx);
		d.z += *(person->ry);
		c.sub(&past);
		c.y = 0;
		
		/* 
		check obvious collision sectors
		
		 1 | 2 | 3
		---|---|---
		 8 | 0 | 4
		---|---|---
		 7 | 6 | 5
			
		0 is not a possible sector for this->past since the bullet must
		be traveling toward the person.
		*/
		int ow = Person::dimsTorso[0]/2;
		int od = Person::dimsTorso[2]/2;
		if (d.x > ow) { //now=1,8,7
			if (c.x < ow) { //past=2,3,4,5,6
				if (d.z > od) { //now=1
					if (c.z > od) { //past=2,3
						return false; //miss top rl
					}
					else { //past=4,5,6
						return true; //hit top left
					}
				}
				else if (d.z < -od) { //now=7
					if (c.z < -od) { //past=5,6
						return false; //miss bottom rl
					}
					else { //past=2,3,4
						return true; //hit bottom left
					}
				}
				else { //now=8
					//TODO from right
					if (c.z > od) { //past=2,3
						return false;
					}
					else if (c.z < -od) { //past=5,6
						return false;
					}
					else { //past=4
						return true; //hit left from right
					} 
				}
			}
			else { //both=1,7,8
				return false;
			}
		}
		else if (d.x < -ow) { //now=3,4,5
			if (c.x > -ow) { //past=1,2,6,7,8
				if (d.z > od) { //now=3
					if (c.z > od) { //past=1,2
						return false; //miss top lr
					}
					else { //past=6,7,8
						return true; //hit top right
					}
				}
				else if (d.z < -od) { //now=5
					if (c.z < -od) { //past=6,7
						return false; //miss bottom lr
					}
					else { //past=1,2,8
						return true; //hit bottom right
					}
				}
				else { //now=4
					//TODO from left
					if (c.z > od) { //past=1,2
						return false;
					}
					else if (c.z < -od) { //past=6,7
						return false;
					}
					else { //past=8
						return true; //hit right from left
					}
				}
			}
			else { //both=3,4,5
				return false;
			}
		}
		else { //now=2,0,6
			if (d.z > od) { //now=2
				if (c.z > od) { //past=1,3
					return false;
				}
				else {
					//TODO from bottom
					if (c.x > ow) { //past=4,5
						return false;
					}
					else if (c.x < -ow) { //past=7,8
						return false;
					}
					else { //past=6
						return true; //hit top from bottom
					}
				}
			}
			else if (d.z < -od) { //now=6
				if (c.z < -od) { //past=5,7
					return false;
				}
				else {
					//TODO from top
					if (c.x > ow) { //past=3,4
						return false;
					}
					else if (c.x < -ow) { //past=1,8
						return false;
					}
					else { //past=2
						return true; //hit bottom from top
					}
				}
			}
			else { //now=0
				return true;
			}
		}
	}
	else {
		return false;
	}
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
	d.x += *(obstacle->rx);
	d.z += *(obstacle->ry);
	d.sub(&location);
	d.y = 0;
	
	if (d.mag() < INFLUENCE_RADIUS + Obstacle::INFLUENCE_RADIUS) {
		//location of previous frame
		ovector c(&(obstacle->location));
		c.x += *(obstacle->rx);
		c.z += *(obstacle->ry);
		c.sub(&past);
		c.y = 0;
		
		/* 
		check obvious collision sectors
		
		 1 | 2 | 3
		---|---|---
		 8 | 0 | 4
		---|---|---
		 7 | 6 | 5
			
		0 is not a possible sector for this->past since the bullet must
		be traveling toward the obstacle.
		*/
		int ow = obstacle->dims[0]/2;
		int od = obstacle->dims[2]/2;
		if (d.x > ow) { //now=1,8,7
			if (c.x < ow) { //past=2,3,4,5,6
				return false; //TODO corner cases
			}
			else { //both=1,7,8
				return false;
			}
		}
		else if (d.x < -ow) { //now=3,4,5
			if (c.x > -ow) { //past=1,2,6,7,8
				return false; //TODO corner cases
			}
			else { //both=3,4,5
				return false;
			}
		}
		else { //now=2,0,6
			if (d.z > od) { //now=6
				return false; //TODO corner cases
			}
			else if (d.z < -od) { //now=2
				return false; //TODO corner cases
			}
			else { //now=0
				return true;
			}
		}
	}
	else {
		return false;
	}
}

ostream & operator <<(ostream &os, const Bullet &ob) {
	os << "Bullet(l=" << ob.location << ",v=" << ob.velocity << ')';
	return os;
}