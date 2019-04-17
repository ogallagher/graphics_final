/*

Owen Gallagher
17 April 2019
Computer Graphics

ovector.h

A 3D vector utility class.
TODO

*/

#ifndef OVECTOR_H
#define OVECTOR_H

#include <cmath>

class ovector {
public:
	float x,y,z;

	ovector() {x=0;y=0;z=0;};
	ovector(ovector *);
	void set(float,float,float);
	void add(ovector *);
	void sub(ovector *);
	void mult(float);
	void div(float);
	float mag();
	void norm();
};

ovector::ovector(ovector *other) {
	x = other->x;
	y = other->y;
	z = other->z;
}

void ovector::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void ovector::add(ovector *other) {
	x += other->x;
	y += other->y;
	z += other->z;
}

void ovector::sub(ovector *other) {
	x -= other->x;
	y -= other->y;
	z -= other->z;
}

void ovector::mult(float k) {
	x *= k;
	y *= k;
	z *= k;
}

void ovector::div(float k) {
	x /= k;
	y /= k;
	z /= k;
}

float ovector::mag() {
	return sqrtf(x*x + y*y + z*z); 
}

//TODO confirm the math is correct here
void ovector::norm() {
	div(mag());
}

#endif