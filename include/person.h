/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics 

person.h

Superclass for all people in the game (player, enemies)

*/

#ifndef PERSON_H
#define PERSON_H

#include "../include/world.h"
#include "../include/ovector.h"

class Person {
public:
	ovector location;
	ovector velocity;
	float heading;

	Person() {
		heading = 0;
	};
	void move();
};

void Person::move() {
	ovector v(&velocity);
	v.mult(World::speed);
	location.add(&velocity);
}

#endif