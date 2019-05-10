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
const double Player::RELOAD_TIME = 2500;
double Player::reload = RELOAD_TIME;

int Player::roomX = 0;
int Player::roomY = 0;

Player::Player() {
	id = nextId++;
}

void Player::move() {
	Person::move();
	
	int *room = getRoom();
	roomX = room[0];
	roomY = room[1];	
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

void Player::shootControl() {
	if (reload > 0) {
		reload-= World::speed;
	}
}

Bullet* Player::shoot() {
	Bullet *bullet = Person::shoot();
	bullet->good = true;
	return bullet;
}

void Player::die() {
	cout << "GAME OVER" << endl;
	cout << "Final Score: " << score << endl;
}