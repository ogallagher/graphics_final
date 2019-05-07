/*

Owen Gallagher, Brian Park
22 April 2019
Computer Graphics

player.cpp

*/

//local headers
#include "../include/player.h"
#include "../include/world.h"

int Player::score = 0;
const double Player::RELOAD_TIME = 50;
double Player::reload = 0;

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
	
	heading = gaze.headingY();
}

void Player::shootControl() {
	if (reload == 0) { //TODO fire at player
		reload = RELOAD_TIME;
	}
	else { //reload
		reload--;
	}
}