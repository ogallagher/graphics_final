/*

Owen Gallagher, Brian Park
5 May 2019
Computer Graphics

material.cpp

*/

//local includes
#include "../include/material.h"

void Material::update() {
	ambient[4] = {amb*color[0],dif*color[1],spec*color[2],alpha};
	diffuse[4] = {amb*color[0],dif*color[1],spec*color[2],alpha};
	specular[4] = {amb*color[0],dif*color[1],spec*color[2],alpha};
}

void setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
	update();
}

void setAlpha(float a) {
	alpha = a;
	update();
}

void setADS(float a, float d, float s) {
	amb = a;
	dif = d;
	spec = s;
	update();
}