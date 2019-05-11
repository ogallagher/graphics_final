/*

Owen Gallagher
11 May 2019
Computer Graphics

text.h

Defines shapes for drawing flat text

*/

#ifndef TEXT_H
#define TEXT_H

//core includes
#include <string>

//local includes
#include "../include/ovector.h"
#include "../include/material.h"

class Text {
private:
	static void drawChar(char); //draws a character in a 1x1 square centered on the origin
	
public:
	Material material;
	int stroke;
	std::string value;
	int length;
	float scale[3];
	ovector location;
	
	Text(std::string val, int siz);
	void display();
	void lower();
};

#endif