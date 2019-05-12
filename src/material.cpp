/*

Owen Gallagher, Brian Park
5 May 2019
Computer Graphics

material.cpp

*/

//local includes
#include "../include/material.h"

void Material::update() {
	ambient[0]=amb*color[0];
	ambient[1]=amb*color[1];
	ambient[2]=amb*color[2];
	ambient[3]=alpha;
	
	diffuse[0]=dif*color[0];
	diffuse[1]=dif*color[1];
	diffuse[2]=dif*color[2];
	diffuse[3]=alpha;
	
	specular[0]=spec*color[0];
	specular[1]=spec*color[1];
	specular[2]=spec*color[2];
	specular[3]=alpha;
}

Material::Material() {
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	alpha = 1;
	amb=1;
	dif=1;
	spec=1;
	update(); //updates opengl values
}

void Material::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
	update();
}

void Material::setAlpha(float a) {
	alpha = a;
	update();
}

void Material::setADS(float a, float d, float s) {
	amb = a;
	dif = d;
	spec = s;
	update();
}

void Material::set(Material *clone) {
	color[0] = clone->color[0];
	color[1] = clone->color[1];
	color[2] = clone->color[2];
	alpha = clone->alpha;
	amb=clone->amb;
	dif=clone->dif;
	spec=clone->spec;
	
	update(); //updates opengl values
}