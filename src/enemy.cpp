/*

Owen Gallagher, Brian Park
4 May 2019
Computer Graphics

enemy.cpp

*/

//core includes
#include <vector>

//local includes
#include "../include/enemy.h"
#include "../include/world.h"
#include "../include/player.h"
#include "../include/bullet.h"
#include "../include/room.h"

using namespace std;

Player *Enemy::player;
const int Enemy::RELOAD_TIME = 50;
const int Enemy::FOV = 30;

Enemy::Enemy(int *rx, int *ry) {
	id = nextId++;
	
	materialBody.setColor(0.5,0,0);
	
	reload = RELOAD_TIME;
	standTime = 500;
	stand = 0;
	standing = false;
	
	this->rx = rx;
	this->ry = ry;
}

bool Enemy::collideBounds() {
	int rd = (World::dims[0] - Obstacle::DIM_MIN) / 2;
	
	if (location.x > rd) {
		location.x = rd - 1;
		return true;
	}
	else if (location.x < -rd) {
		location.x = -rd + 1;
		return true;
	}
	
	if (location.z > rd) {
		location.z = rd - 1;
		return true;
	}
	else if (location.z < -rd) {
		location.z = -rd + 1;
		return true;
	}
	
	return false;
}

void Enemy::loadPlayer(Player *player) {
	Enemy::player = player;
}

void Enemy::followControl() {
	//look at player
	ovector gaze(&(player->location));
	gaze.x += *(player->rx);
	gaze.z += *(player->ry);
	gaze.sub(&location);
	gaze.x -= *rx;
	gaze.z -= *ry;
	heading = gaze.headingY();
	
	if (standing) {
		if (stand < 0) { //change destination
			//TODO complicate with hiding
			
			destination.set(&(player->location));
			destination.x += *(player->rx);
			destination.z += *(player->ry);
			standing = false;
		}
		else { //stand
			stand -= World::speed*(0.02);
		}
	}
	else {
		ovector v(&destination);
		v.sub(&location);
		v.x -= *rx;
		v.z -= *ry;
	
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

Bullet Enemy::shoot() {
	Bullet bullet = Person::shoot();
	bullet.good = false;
	return bullet;
}

void Enemy::stay() {
	velocity.mult(0);
	stand = standTime;
	standing = true;
}

void Enemy::die(bool goodBullet) {
	if (goodBullet) {
		player->score++;
	}
	
	vector<Enemy>::iterator a = World::enemies.begin();
	vector<Enemy>::iterator b = World::enemies.end();
	
	bool found = false;
	while (a != b && !found) {
		if (a->id == id) {
			World::enemies.erase(a);
			found = true;
		}	
		a++;
	}
}