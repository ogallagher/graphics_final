/*

Owen Gallagher, Brian Park
5 May 2019
Computer Graphics

light.cpp

*/

//local includes
#include "../include/light.h"
#include "../include/ovector.h"
#include "../include/obstacle.h"

const int Light::HEIGHT = 30;

void Light::loadTarget(ovector *target) {
	this->target = target;
}

void Light::move() {
	location.set(target);
	location.y += HEIGHT;
}