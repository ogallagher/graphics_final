/*

Owen Gallagher
17 April 2019
Computer Graphics

ovector.h

A 3D vector utility class.

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
	void set(ovector *);
	void add(ovector *);
	void sub(ovector *);
	void mult(float);
	void div(float);
	float mag();
	void norm();
};

#endif