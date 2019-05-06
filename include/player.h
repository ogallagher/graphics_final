/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

player.h

The user's avatar, which inherits from Person.
Controls:
	walk with WASD keys
	aim with cursor
	shoot with mouse left click

*/

#ifndef PLAYER_H
#define PLAYER_H

#include "../include/person.h"
#include "../include/bullet.h"

class Player : public Person {
public:
	void keyControl(); //move with WASD
	void mouseControl(); //look at cursor
	Bullet shoot(); //extend Person::shoot()
};

#endif