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
	w = other->w;
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
	w = other->w;
}

void ovector::set(float x, float y, float z, float w) {
	set(x,y,z);
	this->w = w;
}

void ovector::add(ovector *other) {
	x += other->x;
	y += other->y;
	z += other->z;
	w += other->w;
}

void ovector::sub(ovector *other) {
	x -= other->x;
	y -= other->y;
	z -= other->z;
	w -= other->w;
}

void ovector::mult(float k) {
	x *= k;
	y *= k;
	z *= k;
	w *= k;
}

void ovector::div(float k) {
	x /= k;
	y /= k;
	z /= k;
	w /= k;
}

float ovector::mag() {
	return sqrtf(x*x + y*y + z*z + w*w); 
}

void ovector::norm() {
	div(mag());
}

//TODO verify this math
void ovector::applyMatrix(float m[16]) {
	float a = x*m[0] + y*m[1] + z*m[2] + w*m[3];
	float b = x*m[4] + y*m[5] + z*m[6] + w*m[7];
	float c = x*m[8] + y*m[9] + z*m[10] + w*m[11];
	float d = x*m[12] + y*m[13] + z*m[14] + w*m[15];
	
	set(a,b,c,d);
}

std::ostream & operator <<(std::ostream &os, const ovector &ov) {
	os << '[' << ov.x << ' ' << ov.y << ' ' << ov.z << ' ' << ov.w << ']';
	return os;
}