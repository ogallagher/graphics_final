/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

camera.h

*/

#ifndef CAMERA_H
#define CAMERA_H

#include "../include/world.h"
#include "../include/ovector.h"

class Camera {
public:
	static const int X_TO_TARGET;
	static const int HEIGHT;
	static const int Z_TO_TARGET;
	
	ovector location;
	ovector destination;
	float easing;
	ovector subject;

	Camera() {
		easing = 0.0005;
	};
	void move();
	void follow(ovector *);
};

#endif