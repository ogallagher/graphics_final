/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

world.cpp

*/

#include <iostream> //TODO delete

#include "../include/world.h"
#include "../include/camera.h"

int World::dimsWindow[3] = {600,600,600};
double World::speed = 1;
int World::dims[3] = {200,10,200};
float World::mouse[2] = {0,0};
ovector World::cursor;
bool World::clicked = false;
bool World::keyW = false;
bool World::keyD = false;
bool World::keyS = false;
bool World::keyA = false;
Camera *World::camera = new Camera();

const int World::MOUSE_OFFSET_Y = 5;
const int World::PROJECT_PLANE_OFFSET_Z = World::dimsWindow[2]/20;
float World::pmatrix[16],World::ipmatrix[16],World::mvmatrix[16],World::imvmatrix[16];

void World::loadOSSpeed(int osSpeed) {
	speed *= osSpeed;
}

void World::loadPMatrix() {
	glGetFloatv(GL_PROJECTION_MATRIX,pmatrix);
	if (!invertMatrix(pmatrix,ipmatrix)) {
		cout << "World::loadPMatrix() -> inverse projection failed" << endl;
	}
}

void World::display() {
	loadCamera();

	glPushMatrix();
	
	glScalef(World::dims[0],World::dims[1],World::dims[2]);
	glColor3f(1,1,1);
	glutWireCube(1.0);

	glPopMatrix();
}

string World::describe() {
	string description = "World: [" 
						+ to_string(dims[0]) + "," 
						+ to_string(dims[1]) + ","
						+ to_string(dims[2]) + "] speed="
						+ to_string(speed);
	
	return description;
}

void World::loadCamera() {
	gluLookAt(camera->location.x,camera->location.y,camera->location.z,
			  camera->subject.x,camera->subject.y,camera->subject.z,
			  0,1,0);
}

void World::updateMouse(int x, int y) {
	mouse[0] = 2 * x / (float)dimsWindow[0] - 1; //-1 = left, 1 = right
	mouse[1] = 1 - (2 * y / (float)dimsWindow[1]); //-1 = bottom, 1 = top
}

/*
Adapted from lessons on ray tracing and 3d intersection: 
http://antongerdelan.net/opengl/raycasting.html
Anton Gerdelan 2016
*/
void World::updateCursor() {
	//cursor = m[0] m[1] 1 1
	cursor.set(mouse[0],mouse[1],-1,1);
	
	//cursor = projectionMatrix.inverse() * cursor; z=-1; w=0
	glGetFloatv(GL_PROJECTION_MATRIX,pmatrix);
	invertMatrix(pmatrix,ipmatrix);
	cursor.applyMatrix(ipmatrix);
	cursor.z = -1;
	cursor.w = 0;

	//cursor = modelviewMatrix.inverse() * cursor; normalize
	glGetFloatv(GL_MODELVIEW_MATRIX,mvmatrix);
	invertMatrix(mvmatrix,imvmatrix);
	cursor.applyMatrix(imvmatrix);
	cursor.w = 0;
	cursor.norm();
}

void World::drawCursor() {
	ovector ray(&cursor);
	ray.mult(PROJECT_PLANE_OFFSET_Z);
	//ray.add(&(camera->location));
	
	glPushMatrix();
	
	glTranslatef(ray.x,ray.y,ray.z);
	cout << ray << endl;
	
	if (clicked) {
		glColor3f(1,0,0);
	}
	else {
		glColor3f(1,0,1);
	}
	
	glutSolidSphere(5,5,5);
	
	glPopMatrix();
}

/*
Adapted from StackOverflow answer, from the MESA opengl extension:
https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
*/
bool World::invertMatrix(const float m[16], float invOut[16])
{
    double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}