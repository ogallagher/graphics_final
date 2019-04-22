/*

Owen Gallagher, Brian Park
22 April 2019
Computer Graphics

player.cpp

*/

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
	
	heading = gaze.headingY();
	
	cout << "Player.heading = " << heading << endl;
}