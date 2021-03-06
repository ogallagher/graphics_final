/*

Owen Gallagher, Brian Park
22 April 2019
Computer Graphics

bullet.h

*/

#ifndef BULLET_H
#define BULLET_H

//global headers
#include <iostream>
#include <vector>

//local headers
#include "../include/ovector.h"
#include "../include/material.h"

class Person; //don't include to avoid circular dependency
class Obstacle;
class Enemy;

class Bullet {	
public:
	static const int HEIGHT;
	static const int INFLUENCE_RADIUS;
	
	static int dims[3];
	static float speed;
	static Material material;
	
	ovector location;
	ovector past; //location from one frame ago
	ovector velocity;
	bool good;
	
	Bullet() {};
	Bullet(ovector *l, ovector *v) {
		location.x = l->x;
		location.y = HEIGHT;
		location.z = l->z;
		location.w = 0;
		
		past.set(&location);
		
		velocity.set(v);
		velocity.y = 0;
		velocity.w = 0;
	};
	
	void display();
	void move();
	bool collideBounds(); //returns true on collision
	bool collideEnemies(std::vector<Enemy*> *);
	bool collideObstacles(std::vector<Obstacle*> *);
	bool collidePerson(Person *);
	bool collideObstacle(Obstacle *);
	
	friend std::ostream & operator <<(std::ostream &, const Bullet &);
};

#endif