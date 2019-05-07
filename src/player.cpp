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
int Player::worldX = 0;
int Player::worldY = 0;

void Player::move() {
	Person::move();
	
	int newX = location.x/Room::DIM_MAX;
	int newY = location.z/Room::DIM_MAX;
	
	if (newX != roomX) {
		int x = 0;
		int a = World::ROOMS_ALL;
		if (newX < roomX) {
			x = a;
		}
		
		for (int y=0; y<=a; y++) {
			World::loadRoom(x,y);
		}
	}
	else if (newY != roomY) {
		int y = 0;
		int a = World::ROOMS_ALL;
		if (newY < roomY) {
			y = a;
		}
		
		for (int x=0; x<=a; x++) {
			World::loadRoom(x,y);
		}
	}
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