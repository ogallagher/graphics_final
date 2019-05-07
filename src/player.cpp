/*

Owen Gallagher, Brian Park
22 April 2019
Computer Graphics

player.cpp

*/

//local headers
#include "../include/player.h"
#include "../include/world.h"
#include "../include/bullet.h"
#include "../include/room.h"

int Player::score = 0;
const double Player::RELOAD_TIME = 50;
double Player::reload = 0;

int Player::roomX = 0;
int Player::roomY = 0;

Player::Player() {
	id = nextId++;
}

void Player::move() {
	Person::move();
	
	int rd = World::dims[0];
	roomX = floor((location.x + rd/2) / rd);
	roomY = floor((location.z + rd/2) / rd);
	cout << roomX << " " << roomY << "="
		 << World::roomIndex(roomX) << " " << World::roomIndex(roomY)
	     << endl;
}

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

Bullet Player::shoot() {
	Bullet bullet = Person::shoot();
	bullet.good = true;
	return bullet;
}

void Player::die() {
	//TODO end game
	cout << "GAME OVER" << endl;
}