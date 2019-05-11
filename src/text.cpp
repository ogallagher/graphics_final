/*

Owen Gallagher
11 May 2019
Computer Graphics 

text.cpp

*/

//core includes
#include <string>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION //Mac opengl
#include <GLUT/glut.h>
#else
#include <GL/glut.h> //Windows opengl
#endif

//local includes
#include "../include/text.h"
#include "../include/world.h"

Text::Text(string text, int size) {
	value = text;
	length = value.length();
	
	lower();
	
	material.setColor(1,1,1);
	material.setADS(1,0,0);
}

Text::drawChar(char c) {
	glBegin(GL_LINES);
	
	switch (c) {
		case '0':
		case 'o':
			glVertexf(-0.5,-0.5);
			glVertexf(0.5,-0.5);
			glVertexf(0.5,-0.5);
			glVertexf(0.5,0.5);
			glVertexf(0.5,0.5);
			glVertexf(-0.5,0.5);
			glVertexf(-0.5,0.5);
			glVertexf(-0.5,-0.5);
			break;
		
		case '1':
		case 'i':
			glVertexf(0,-0.5);
			glVertexf(0,0.5);
			break;
		
		case '2':
		case 'b':
			break;
			
		case '3':
			break;
			
		default:
			break;
	}
	
	glEnd();
}

Text::display() {
	glPushMatrix();
	
	//transforms
	//glRotatef(90,1,0,0);
	glScalef(scale);
	glTranslatef(location.x,location.y,location.z);
	
	//material
	World::loadMaterial(&material);
	
	//shapes
	char c;
	for (int i=0; i<length; i++) {
		drawChar(value[i]);
	}
	
	glPopMatrix();
}

Text::lower() {
	char c;
	for (int i=0; i<length; i++) {
		c = value[i];
		
		if (c >= 'A' && c <= 'Z') {
			c += 32;
		}
	}
}