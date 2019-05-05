/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

*/

//global headers
#include <cmath>
#include <vector>

//local headers
#include "../include/world.h"
#include "../include/person.h"
#include "../include/bullet.h"
#include "../include/enemy.h"

int Person::dimsHead[3] = {2,2,2};
int Person::dimsTorso[3] = {3,5,3};
int Person::dimsArm[3] = {1,5,1};
int Person::dimsLeg[3] = {1,4,1};
float Person::speed = 0.02;
const int Person::NECK_HEIGHT = 1;
const int Person::INFLUENCE_RADIUS = (dimsTorso[0] + dimsArm[1])*3;

void Person::move() {
	ovector v(&velocity);
	v.mult(World::speed);
	location.add(&v);
	
	if (velocity.mag() >= speed) {
		headingLegs = v.headingY()+90;
	}
}

Bullet Person::shoot() {
	float bh = heading/180*3.141593;
	
	ovector bl(cos(bh),0,-sin(bh));
	ovector bv(&bl);
	
	bl.mult(dimsTorso[2]/2 + Bullet::dims[2]/2);
	bl.add(&location);
	
	bv.mult(Bullet::speed);
	
	return Bullet(&bl,&bv);
}

void Person::drawHead() {
	glPushMatrix();

	//transforms
	glTranslatef(0,(dimsTorso[1]+dimsHead[1])/2 + NECK_HEIGHT,0);
	glScalef(dimsHead[0],dimsHead[1],dimsHead[2]);
	
	//material properties
	glColor3f(colorHead[0],colorHead[1],colorHead[2]);
	
	//primitive
	glutSolidCube(1);

	glPopMatrix();
}

void Person::drawArmL() {
	glPushMatrix();

	glTranslatef(-dimsTorso[0]/2.0 - dimsArm[0]/2.0,0,0);
	glScalef(dimsArm[0],dimsArm[1],dimsArm[2]);
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::drawArmR() {
	glPushMatrix();
	
	glTranslatef(dimsTorso[0]/2.0 + dimsArm[0]/2.0,0,0);
	glScalef(dimsArm[0],dimsArm[1],dimsArm[2]);
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::drawArms() {
	glColor3f(colorHead[0],colorHead[1],colorHead[2]);
	
	glPushMatrix();
	
	glTranslatef(0,dimsArm[1]/2,0); //align shoulder with neck
	glRotatef(-90,1,0,0); //rotate around shoulder
	glTranslatef(0,-dimsArm[1]/2,0); //shoulder is origin
	
	drawArmL();
	drawArmR();
	
	glPopMatrix();
}

void Person::drawLegL() {
	glPushMatrix();
	
	glRotatef(headingLegs,0,1,0); //rotate around spine
	glTranslatef(0,-dimsTorso[1]/2,0); //align hip with bottom of torso
	if (velocity.mag() >= speed*0.9) {
		glRotatef(-sin(World::t * 4) * 45,1,0,0); //rotate around hip
	}
	glTranslatef(0,-dimsLeg[1]/2,0); //hip is origin
	
	glTranslatef(-dimsTorso[0]/2 + dimsLeg[0]/2,0,0);
	glScalef(dimsLeg[0],dimsLeg[1],dimsLeg[2]);
	glRotatef(90,0,1,0); //flip hip rotation
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::drawLegR() {
	glPushMatrix();
	
	glRotatef(headingLegs,0,1,0); //rotate around spine
	glTranslatef(0,-dimsTorso[1]/2,0); //align hip with bottom of torso
	if (velocity.mag() >= speed*0.9) {
		glRotatef(sin(World::t * 4) * 45,1,0,0); //rotate around hip
	}
	glTranslatef(0,-dimsLeg[1]/2,0); //hip is origin
	
	glTranslatef(dimsTorso[0]/2 - dimsLeg[0]/2,0,0);
	glScalef(dimsLeg[0],dimsLeg[1],dimsLeg[2]);
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::drawLegs() {
	glColor3f(colorHead[0],colorHead[1],colorHead[2]);
	
	drawLegL();
	drawLegR();	
}

void Person::drawTorso() {
	glPushMatrix();
	
	//inherited transforms
	glTranslatef(0,dimsLeg[1] + dimsTorso[1]/2,0);
	
	//draw children
	drawLegs();
	
	glRotatef(heading+90,0,1,0);
	drawHead();
	drawArms();
	
	//local transforms
	glScalef(dimsTorso[0],dimsTorso[1],dimsTorso[2]);
	
	//material properties
	glColor3f(colorBody[0],colorBody[1],colorBody[2]);
	
	//primitive
	glutSolidCube(1);
	
	glPopMatrix();
}

void Person::display() {
	glPushMatrix();

	glTranslatef(location.x,location.y,location.z);
	
	drawTorso();

	glPopMatrix();
}

bool Person::collideObstacles(vector<Obstacle> *obstacles) {
	bool collided = false;
	
	for (vector<Obstacle>::iterator oit=obstacles->begin(); oit!=obstacles->end() && !collided; oit++) {
		if (collideObstacle(&(*oit))) {
			collided = true;
		}
	}
	
	return collided;
}

bool Person::collideObstacle(Obstacle *obstacle) {
	//difference between locations
	ovector d(&(obstacle->location));
	d.y = 0;
	d.sub(&location);

	//initial distance check
	if (d.mag() < INFLUENCE_RADIUS + Obstacle::INFLUENCE_RADIUS) {		
		//subtract dimensions around each object
		int dx = abs(d.x) - (dimsTorso[0] + dimsArm[1] + obstacle->dims[0])/2;
		int dz = abs(d.z) - (dimsTorso[2] + dimsArm[1] + obstacle->dims[2])/2;
	
		if (dx < 0 && dz < 0) {
			//is touching obstacle somewhere; push person outside of obstacle
			if (dx > dz) {
				if (d.x > 0) {
					location.x += dx;
				}
				else {
					location.x -= dx;
				}
			}
			else {
				if (d.z > 0) {
					location.z += dz;
				}
				else {
					location.z -= dz;
				}
			}

			return true;
		}
		else {
			return false;
		}
	}
	else {
		//not close enough to obstacle for any collision to occur
		return false;
	}
}

bool Person::collidePeople(vector<Person> *people) {
	bool collided = false;
	
	for (vector<Person>::iterator pit=people->begin(); pit!=people->end() && !collided; pit++) {
		if (collidePerson(&(*pit))) {
			collided = true;
		}
	}
	
	return collided;
}

bool Person::collidePeople(vector<Enemy> *enemies) {
	bool collided = false;
	
	for (vector<Enemy>::iterator eit=enemies->begin(); eit!=enemies->end() && !collided; eit++) {
		if (collidePerson(static_cast<Person*>(&(*eit)))) {
			collided = true;
		}
	}
	
	return collided;
}

bool Person::collidePerson(Person *person) {
	//difference between locations
	ovector d(&(person->location));
	d.y = 0;
	d.sub(&location);

	//initial distance check
	if (d.mag() < INFLUENCE_RADIUS+INFLUENCE_RADIUS) {		
		//subtract dimensions around each object
		int dx = abs(d.x) - (dimsTorso[0] + dimsArm[1]);
		int dz = abs(d.z) - (dimsTorso[2] + dimsArm[1]);
	
		if (dx < 0 && dz < 0) {
			//is touching obstacle somewhere; push person outside of obstacle
			if (dx > dz) {
				if (d.x > 0) {
					location.x += dx;
				}
				else {
					location.x -= dx;
				}
			}
			else {
				if (d.z > 0) {
					location.z += dz;
				}
				else {
					location.z -= dz;
				}
			}

			return true;
		}
		else {
			return false;
		}
	}
	else {
		//not close enough to obstacle for any collision to occur
		return false;
	}
}