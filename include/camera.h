/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

camera.h

*/

#ifndef CAMERA_H
#define CAMERA_H

#include "../include/ovector.h"

class Camera {
public:
	ovector location;
	ovector destination;
	float easing;
	ovector subject;

	Camera() {
		easing = 0.2;
	};
	void move();
};

void Camera::move() {
	ovector v(&destination);
	v.sub(&location);
	v.mult(easing*World::speed);

	location.add(&v);
}

#endif