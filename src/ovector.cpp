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
	if (k != 0) {
		x /= k;
		y /= k;
		z /= k;
		w /= k;
	}
}

float ovector::mag() {
	if (x==0 && y==0 && z==0 && w==0) {
		return 0;
	}
	else {
		return sqrtf(x*x + y*y + z*z + w*w); 
	}
}

void ovector::norm() {
	div(mag());
}

void ovector::applyMatrix(float m[16]) {
	//column major
	float a = x*m[0] + y*m[4] + z*m[8] + w*m[12];
	float b = x*m[1] + y*m[5] + z*m[9] + w*m[13];
	float c = x*m[2] + y*m[6] + z*m[10] + w*m[14];
	float d = x*m[3] + y*m[7] + z*m[11] + w*m[15];
	
	set(a,b,c,d);
}

std::ostream & operator <<(std::ostream &os, const ovector &ov) {
	os << '[' << ov.x << ' ' << ov.y << ' ' << ov.z << ' ' << ov.w << ']';
	return os;
}