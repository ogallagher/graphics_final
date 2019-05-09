/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

camera.cpp

*/

#include "../include/world.h"
#include "../include/ovector.h"
#include "../include/camera.h"

const int Camera::X_TO_TARGET = 100;
const int Camera::HEIGHT = 100;
const int Camera::Z_TO_TARGET = 100;

void Camera::move() {
	//keep a certain distance
	int xd = target->x-location.x;
	if (xd > X_TO_TARGET) {
		destination.x = target->x - X_TO_TARGET;
	}
	else if (xd < -X_TO_TARGET) {
		destination.x = target->x + X_TO_TARGET;
	}
	destination.y = HEIGHT;
	destination.z = target->z + Z_TO_TARGET;
	
	ovector v(&destination);
	v.sub(&location);
	v.mult(easing * World::osSpeed);

	location.add(&v);
}

void Camera::loadTarget(ovector *t) {
	target = t;
}