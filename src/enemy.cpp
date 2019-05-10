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
#include "../include/player.h"
#include "../include/world.h"
#include "../include/room.h"
#include "../include/bullet.h"

using namespace std;

const int Enemy::FOV = 30;

Enemy::Enemy(int *rx, int *ry) {
	id = nextId++;
	
	this->rx = rx;
	this->ry = ry;
	
	materialBody.setColor(0.5,0,0);
	
	reloadTime = 2500 * World::getRandom() + 500;
	reload = reloadTime;
	
	standTime = 5000 * World::getRandom() + 1000;
	stand = standTime;
	standing = false;
	dead = false;
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

void Enemy::followControl() {
	Player *player = World::player;
	
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
			destination.set(&(player->location));
			destination.x += *(player->rx);
			destination.z += *(player->ry);
			standing = false;
		}
		else { //stand
			stand -= World::speed;
		}
	}
	else {
		ovector v(&destination);
		v.x += *(player->rx);
		v.z += *(player->ry);
		v.sub(&location);
		v.x -= *rx;
		v.z -= *ry;

		if (v.mag() < Person::dimsTorso[0] + Person::dimsArm[1]) { //arrive
			stay();
		}
		else {
			v.norm();
			v.mult(speed);
			velocity.set(&v);
		}
	}
}

void Enemy::shootControl() {	
	if (reload <= 0) {
		World::bullets.push_back(shoot());
		reload = reloadTime;
	}
	else { //reload
		reload-=World::speed;
	}
}

Bullet* Enemy::shoot() {
	Bullet *bullet = Person::shoot();
	bullet->good = false;
	return bullet;
}

void Enemy::stay() {
	velocity.mult(0);
	stand = standTime;
	standing = true;
}

void Enemy::die(bool goodBullet) {
	if (goodBullet) {
		cout << "Current Score: " << (++World::player->score) << endl;
	}
	
	//remove pointer from room
	int *roomId = getRoom();
	Room *room = &World::rooms[World::roomIndex(roomId[1])][World::roomIndex(roomId[0])];
	vector<Enemy *>::iterator a = room->enemies.begin();
	vector<Enemy *>::iterator b = room->enemies.end();
	
	bool found = false;
	while (a != b && !found) {
		if ((*a)->id == id) {
			room->enemies.erase(a);
			found = true;
			cout << "enemy" << id << " died" << endl;
		}
		else {
			a++;
		}	
	}
}