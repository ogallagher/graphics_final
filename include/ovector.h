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
#include <iostream>

class ovector {
public:
	float x,y,z,w;

	ovector() {x=0;y=0;z=0;w=0;};
	ovector(ovector *);
	void set(float,float,float);
	void set(float,float,float,float);
	void set(ovector *);
	void add(ovector *);
	void sub(ovector *);
	void mult(float);
	void div(float);
	float mag();
	void norm();
	float headingY(); //heading around the y axis
	void applyMatrix(float [16]);
	
	friend std::ostream & operator <<(std::ostream &, const ovector &);
};

#endif