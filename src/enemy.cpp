/*

Owen Gallagher, Brian Park
4 May 2019
Computer Graphics

enemy.cpp

*/

#include <iostream> //TODO delete

//local includes
#include "../include/enemy.h"
#include "../include/world.h"
#include "../include/player.h"

Player *Enemy::player;
const int Enemy::RELOAD_TIME = 50;
const int Enemy::FOV = 30;

Enemy::Enemy() {
	colorBody[0] = 0.5;
	colorBody[1] = 0;
	colorBody[2] = 0;
	
	reload = RELOAD_TIME;
	standTime = 500;
	stand = 0;
	standing = false;
}

void Enemy::loadPlayer(Player *player) {
	Enemy::player = player;
}

void Enemy::followControl() {
	//look at player
	ovector gaze(&(player->location));
	gaze.sub(&location);
	heading = gaze.headingY();
	
	if (standing) {
		if (stand == 0) { //change destination
			//TODO complicate with hiding
			
			destination.set(&(player->location));
			standing = false;
		}
		else { //stand
			stand--;
		}
	}
	else {
		ovector v(&destination);
		v.sub(&location);
	
		if (v.mag() < Person::dimsTorso[0]/2 + Person::dimsArm[1]) { //arrive
			stay();
		}
		else { //move
			v.norm();
			v.mult(speed);
			velocity.set(&v);
		}
	}
}

void Enemy::shootControl() {
	if (reload == 0) { //TODO fire at player
		reload = RELOAD_TIME;
	}
	else { //reload
		reload--;
	}
}

void Enemy::stay() {
	velocity.mult(0);
	stand = standTime;
	standing = true;
}