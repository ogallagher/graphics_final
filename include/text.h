/*

Owen Gallagher
11 May 2019
Computer Graphics

text.h

Defines shapes for drawing flat text in 3D space with
transforms, material properties, and interactivity;

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
	static const float SPACING;
	
	static void drawChar(char); //draws a centered character in a 1x1 square
	
	void lower(); //converts to lower case
	void measure(); //sets dims
	
public:
	Material material;
	int stroke;
	std::string value;
	int length;
	float scale[2];
	ovector location;
	int w,h; //dimensions halved
	
	Text();
	Text(std::string text, int sx, int sy);
	void display();
	bool selected();
};

#endif