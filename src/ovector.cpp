/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

ovector.cpp

*/

#include "../include/ovector.h"

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

void ovector::set(ovector *other) {
	x = other->x;
	y = other->y;
	z = other->z;
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

std::ostream & operator <<(std::ostream &os, const ovector &ov) {
	os << '[' << ov.x << ' ' << ov.y << ' ' << ov.z << ']';
	return os;
}