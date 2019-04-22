/*

Owen Gallagher, Brian Park
22 April 2019
Computer Graphics

bullet.h

*/

#ifndef BULLET_H
#define BULLET_H

//local headers
#include "../include/ovector.h"

class Bullet {
public:
	static const int HEIGHT;
	
	static int dims[3];
	static float speed;
	
	ovector location;
	ovector velocity;
	
	Bullet(ovector *l, ovector *v) {
		location.x = l->x;
		location.y = HEIGHT;
		location.z = l->z;
		
		velocity.set(v);
	};
	
	void display();
	void move();
};

#endif