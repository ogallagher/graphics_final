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

class Person; //don't include to avoid circular dependency
class Obstacle;

class Bullet {	
public:
	static const int HEIGHT;
	static const int INFLUENCE_RADIUS;
	
	static int dims[3];
	static float speed;
	
	ovector location;
	ovector past; //location from one frame ago
	ovector velocity;
	
	Bullet() {};
	Bullet(ovector *l, ovector *v) {
		location.x = l->x;
		location.y = HEIGHT;
		location.z = l->z;
		location.w = 0;
		
		past.set(&location);
		
		velocity.set(v);
		
	};
	
	void display();
	void move();
	bool collideBounds(); //returns true on collision
	bool collidePeople(std::vector<Person> *);
	bool collideObstacles(std::vector<Obstacle> *);
	bool collidePerson(Person *);
	bool collideObstacle(Obstacle *);
	
	friend std::ostream & operator <<(std::ostream &, const Bullet &);
};

#endif