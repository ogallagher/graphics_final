/*

Owen Gallagher, Brian Park
22 April 2019
Computer Graphics

player.cpp

*/

//core headers
#include <cmath>

//local headers
#include "../include/player.h"
#include "../include/world.h"

void Player::keyControl() {
	ovector keycontrol;
	if (World::keyW) { //north
		keycontrol.z -= 1;
	}
	if (World::keyD) { //east
		keycontrol.x += 1;
	}
	if (World::keyS) { //south
		keycontrol.z += 1;
	}
	if (World::keyA) { //west
		keycontrol.x -= 1;
	}
	keycontrol.norm();
	keycontrol.mult(speed);
	velocity.set(&keycontrol);
}

void Player::mouseControl() {
	ovector gaze(&World::cursor);
	gaze.sub(&location);
	
	float x = gaze.x;
	float z = -gaze.z;
	
	if (x == 0) {
		//the zero-denominator cases
		if (z > 0) {
			heading = 90;
		}
		else {
			heading = -90;
		}
	}
	else {
		//most cases
		heading = abs(atan(z/x)) / 3.141593 * 180; //in degrees
		
		//quadrant correction
		if (x > 0) {
			if (z > 0) {
				//q1
			}
			else {
				//q4
				heading = 360-heading;
			}
		}
		else {
			if (z > 0) {
				//q2
				heading = 180-heading;
			}
			else {
				//q3
				heading = 180+heading;
			}
		}
	}
	
	cout << "Player.heading = " << heading << endl;
}