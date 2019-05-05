/*

Owen Gallagher, Brian Park
5 May 2019
Computer Graphics

material.h

Class to represent OpenGL material properties.

*/

#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
private:
	float ambient[4];
	float diffuse[4];
	float specular[4];
	
	float color[3];
	float alpha;
	float amb,dif,spec;
	
	void update();
	
public:
	Material() {
		color[3] = {0,0,0}
		alpha = 1;
		amb=1;
		dif=1;
		spec=1;
		
		update(); //updates opengl values
	}
	void setColor(float r, float g, float b);
	void setAlpha(float a);
	void setADS(float a, float d, float s);
};

#endif