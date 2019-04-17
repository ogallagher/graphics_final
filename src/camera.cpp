/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

camera.cpp

*/

#include "../include/camera.h"

void Camera::move() {
	ovector v(&destination);
	v.sub(&location);
	v.mult(easing*World::speed);

	location.add(&v);
}