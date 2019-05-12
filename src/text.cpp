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

//macros (final semicolon not included)
#define TOP_ACROSS glVertex3f(-0.5,0.5,0); glVertex3f(0.5,0.5,0)
#define CENTER_ACROSS glVertex3f(-0.5,0,0); glVertex3f(0.5,0,0)
#define BOTTOM_ACROSS glVertex3f(-0.5,-0.5,0); glVertex3f(0.5,-0.5,0)
#define LEFT_DOWN glVertex3f(-0.5,0.5,0); glVertex3f(-0.5,-0.5,0)
#define LEFT_DOWN_TOP glVertex3f(-0.5,0.5,0); glVertex3f(-0.5,0,0)
#define LEFT_DOWN_BOTTOM glVertex3f(-0.5,0,0); glVertex3f(-0.5,-0.5,0)
#define CENTER_DOWN glVertex3f(0,0.5,0); glVertex3f(0,-0.5,0)
#define CENTER_DOWN_TOP glVertex3f(0,0.5,0); glVertex3f(0,0,0)
#define CENTER_DOWN_BOTTOM glVertex3f(0,0,0); glVertex3f(0,-0.5,0)
#define RIGHT_DOWN glVertex3f(0.5,0.5,0); glVertex3f(0.5,-0.5,0)
#define RIGHT_DOWN_TOP glVertex3f(0.5,0.5,0); glVertex3f(0.5,0,0)
#define RIGHT_DOWN_BOTTOM glVertex3f(0.5,0,0); glVertex3f(0.5,-0.5,0)

using namespace std;

Text::Text() {
	length = 0;
	
	scale[0] = 1;
	scale[1] = 1;
	
	w = 0;
	h = 0;
	
	material.setColor(1,1,0); //white
	material.setADS(1,0,0); //ambient
	stroke = 4;
}

Text::Text(string text, int sx, int sy) {
	Text();
	
	value = text;
	length = value.length();
	scale[0] = sx;
	scale[1] = sy;
	
	lower();
	measure();
}

void Text::drawChar(char c) {
	glBegin(GL_LINES);
	
	switch (c) {
		case '0':
		case 'o':
		TOP_ACROSS;
		BOTTOM_ACROSS;
		LEFT_DOWN;
		RIGHT_DOWN;
		break;
		
		case '1':
		case 'i':
		CENTER_DOWN;
		break;
		
		case '2':
		TOP_ACROSS;
		CENTER_ACROSS;
		BOTTOM_ACROSS;
		RIGHT_DOWN_TOP;
		LEFT_DOWN_BOTTOM;
		break;
		
		case '3':
		TOP_ACROSS;
		CENTER_ACROSS;
		BOTTOM_ACROSS;
		RIGHT_DOWN;
		break;
		
		case '4':
		RIGHT_DOWN;
		LEFT_DOWN_TOP;
		CENTER_ACROSS;
		break;
		
		case '5':
		TOP_ACROSS;
		CENTER_ACROSS;
		BOTTOM_ACROSS;
		LEFT_DOWN_TOP;
		RIGHT_DOWN_BOTTOM;
		break;
		
		case '6':
		TOP_ACROSS;
		CENTER_ACROSS;
		BOTTOM_ACROSS;
		LEFT_DOWN;
		RIGHT_DOWN_BOTTOM;
		break;
		
		case '7':
		TOP_ACROSS;
		RIGHT_DOWN;
		break;
		
		case '8':
		case 'b':
		TOP_ACROSS;
		CENTER_ACROSS;
		BOTTOM_ACROSS;
		LEFT_DOWN;
		RIGHT_DOWN;
		break;
		
		case '9':
		TOP_ACROSS;
		RIGHT_DOWN;
		LEFT_DOWN_TOP;
		CENTER_ACROSS;
		break;
		
		default:
		break;
	}
	
	glEnd();
}

void Text::display() {
	glPushMatrix();
	
	//transforms
	glTranslatef(location.x,location.y,location.z);
	glScalef(scale[0],scale[1],1);
	//glRotatef(90,1,0,0);
	
	//material
	World::loadMaterial(&material);
	glLineWidth(stroke);
	
	//characters
	char c;
	for (int i=0; i<length; i++) {
		glTranslatef(1,0,0);
		
		c = value[i];
		
		if (c == '\n') {
			glTranslatef(0,-1,0);
		}
		else {
			drawChar(c);
		}
	}
	
	glPopMatrix();
}

bool Text::selected() {
	if (World::clicked) {
		//find text-World::cursor distance (assuming they're on the same plane)
		ovector d(&World::cursor);
		d.sub(&location);
		
		if (d.x > -w && d.x < w && d.z > -h && d.z < h) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void Text::lower() {
	char c;
	for (int i=0; i<length; i++) {
		c = value[i];
		
		if (c >= 'A' && c <= 'Z') {
			c += 32;
		}
		
		value[i] = c;
	}
}

void Text::measure() {
	char c;
	w=0;
	h=0;
	int r=0;
	
	for (int i=0; i<length; i++) {
		c = value[i];
		
		if (c == '\n') {
			h++;
			if (r > w) {
				w = r;
			}
			r=0;
		}
		else {
			r++;
		}
	}
	if (r > w) {
		w = r;
	}
	
	w *= scale[0] * 0.5;
	h *= scale[1] * 0.5;
}