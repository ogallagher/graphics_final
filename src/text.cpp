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
#include "../include/bullet.h"

const float Text::SPACING = 0.1;

//macros (final semicolon not included)
#define TOP_ACROSS glVertex3f(-0.5+SPACING,0.5-SPACING,0); glVertex3f(0.5-SPACING,0.5-SPACING,0)
#define CENTER_ACROSS glVertex3f(-0.5+SPACING,0,0); glVertex3f(0.5-SPACING,0,0)
#define BOTTOM_ACROSS glVertex3f(-0.5+SPACING,-0.5+SPACING,0); glVertex3f(0.5-SPACING,-0.5+SPACING,0)
#define LEFT_DOWN glVertex3f(-0.5+SPACING,0.5-SPACING,0); glVertex3f(-0.5+SPACING,-0.5+SPACING,0)
#define LEFT_DOWN_TOP glVertex3f(-0.5+SPACING,0.5-SPACING,0); glVertex3f(-0.5+SPACING,0,0)
#define LEFT_DOWN_BOTTOM glVertex3f(-0.5+SPACING,0,0); glVertex3f(-0.5+SPACING,-0.5+SPACING,0)
#define CENTER_DOWN glVertex3f(0,0.5-SPACING,0); glVertex3f(0,-0.5+SPACING,0)
#define CENTER_DOWN_TOP glVertex3f(0,0.5-SPACING,0); glVertex3f(0,0,0)
#define CENTER_DOWN_BOTTOM glVertex3f(0,0,0); glVertex3f(0,-0.5+SPACING,0)
#define RIGHT_DOWN glVertex3f(0.5-SPACING,0.5-SPACING,0); glVertex3f(0.5-SPACING,-0.5+SPACING,0)
#define RIGHT_DOWN_TOP glVertex3f(0.5-SPACING,0.5-SPACING,0); glVertex3f(0.5-SPACING,0,0)
#define RIGHT_DOWN_BOTTOM glVertex3f(0.5-SPACING,0,0); glVertex3f(0.5-SPACING,-0.5+SPACING,0)
#define TOP_LEFT glVertex3f(-0.5+SPACING,0.5-SPACING,0); glVertex3f(0.5-SPACING,0,0)
#define TOP_RIGHT glVertex3f(0.5-SPACING,0.5-SPACING,0); glVertex3f(-0.5+SPACING,0,0)
#define BOTTOM_LEFT glVertex3f(-0.5+SPACING,0,0); glVertex3f(0.5-SPACING,-0.5+SPACING,0)
#define BOTTOM_RIGHT glVertex3f(0.5-SPACING,0,0); glVertex3f(-0.5+SPACING,-0.5+SPACING,0)

using namespace std;

Text::Text() {
	length = 0;
	scale[0] = 1;
	scale[1] = 1;
	w = 0;
	h = 0;
	horizontal = true;
	hovered = false;
}

Text::Text(string text, int sx, int sy) {
	material.setColor(1.0,1.0,1.0); //white
	material.setADS(1,0,0); //ambient
	materialHovered.set(&material);
	
	value = text;
	length = value.length();
	scale[0] = sx;
	scale[1] = sy;
	horizontal = true;
	hovered = false;
	
	lower();
	measure();
}

void Text::set(string text) {
	value = text;
	length = value.length();
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
		case 'z':
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
		case 's':
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
		
		case 'a':
		TOP_ACROSS;
		CENTER_ACROSS;
		LEFT_DOWN;
		RIGHT_DOWN;
		break;
		
		case 'c':
		TOP_ACROSS;
		BOTTOM_ACROSS;
		LEFT_DOWN;
		break;
		
		case 'd':
		LEFT_DOWN;
		TOP_LEFT;
		BOTTOM_RIGHT;
		break;
		
		case 'e':
		TOP_ACROSS;
		CENTER_ACROSS;
		BOTTOM_ACROSS;
		LEFT_DOWN;
		break;
		
		case 'f':
		TOP_ACROSS;
		CENTER_ACROSS;
		LEFT_DOWN;
		break;
		
		case 'g':
		TOP_ACROSS;
		BOTTOM_ACROSS;
		LEFT_DOWN;
		RIGHT_DOWN_BOTTOM;
		break;
		
		case 'h':
		CENTER_ACROSS;
		LEFT_DOWN;
		RIGHT_DOWN;
		break;
		
		case 'j':
		BOTTOM_ACROSS;
		RIGHT_DOWN;
		LEFT_DOWN_BOTTOM;
		break;
		
		case 'k':
		LEFT_DOWN;
		TOP_RIGHT;
		BOTTOM_LEFT;
		break;
		
		case 'l':
		LEFT_DOWN;
		BOTTOM_ACROSS;
		break;
		
		case 'm':
		TOP_ACROSS;
		LEFT_DOWN;
		CENTER_DOWN;
		RIGHT_DOWN;
		break;
		
		case 'n':
		TOP_LEFT;
		LEFT_DOWN;
		RIGHT_DOWN;
		break;
		
		case 'p':
		TOP_ACROSS;
		CENTER_ACROSS;
		LEFT_DOWN;
		RIGHT_DOWN_TOP;
		break;
		
		case 'q':
		TOP_ACROSS;
		BOTTOM_ACROSS;
		LEFT_DOWN;
		RIGHT_DOWN;
		BOTTOM_LEFT;
		break;
		
		case 'r':
		LEFT_DOWN;
		CENTER_ACROSS;
		TOP_LEFT;
		BOTTOM_LEFT;
		break;
		
		case 't':
		TOP_ACROSS;
		CENTER_DOWN;
		break;
		
		case 'u':
		LEFT_DOWN;
		BOTTOM_ACROSS;
		RIGHT_DOWN;
		break;
		
		case 'v':
		RIGHT_DOWN;
		LEFT_DOWN_TOP;
		BOTTOM_LEFT;
		break;
		
		case 'w':
		LEFT_DOWN;
		BOTTOM_ACROSS;
		RIGHT_DOWN;
		CENTER_DOWN;
		break;
		
		case 'x':
		BOTTOM_LEFT;
		BOTTOM_RIGHT;
		break;
		
		case 'y':
		RIGHT_DOWN;
		TOP_LEFT;
		break;
		
		case '>':
		TOP_LEFT;
		BOTTOM_RIGHT;
		break;
		
		default: //whitespace
		break;
	}
	
	glEnd();
}

void Text::display() {
	glPushMatrix();
	
	//transforms
	if (horizontal) {
		glTranslatef(location.x - (w - scale[0]/2),World::CURSOR_HEIGHT,location.z);
		glRotatef(-90,1,0,0);
	}
	else {
		glTranslatef(location.x - (w - scale[0]/2),location.y,location.z);
	}
	glScalef(scale[0],scale[1],1);
	
	//material
	if (hovered) {
		World::loadMaterial(&materialHovered);
	}
	else {
		World::loadMaterial(&material);
	}
		
	//characters
	char c;
	int x=0;
	for (int i=0; i<length; i++) {
		c = value[i];
		
		if (c == '\n') {
			glTranslatef(-x,-1,0);
			x = 0;
		}
		else {
			drawChar(c);
			glTranslatef(1,0,0);
			x += 1;
		}
	}
	
	glPopMatrix();
}

bool Text::selected() {
	//find text-World::cursor distance (assuming they're on the same plane)
	ovector d(&World::cursor);
	d.sub(&location);
	
	if (d.x > -w && d.x < w && d.z > -h && d.z < h) {
		hovered = true;
	}
	else {
		hovered = false;
	}
	
	return (World::clicked && hovered);
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
	h=1;
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