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

using namespace std;

unsigned int Enemy::nextId = 0;
Player *Enemy::player;
const int Enemy::FOV = 30;
float randReload = 0;

Enemy::Enemy() {
	id = nextId++;
	randReload = World::getRandom() * (1000-300) + 300;
	materialBody.setColor(0.5,0,0);
	RELOAD_TIME = 3000 + randReload;
	reload = RELOAD_TIME;
	standTime = 500*World::getRandom();
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
		if (stand < 0) { //change destination
			//TODO complicate with hiding
			
			destination.set(&(player->location));
			standing = false;
		}
		else { //stand
			stand -= World::speed*(0.1);
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
			v.mult(speed*World::getRandom());
			velocity.set(&v);
		}
	}
}

void Enemy::shootControl() {
	if (reload <= 0) {
		World::bullets.push_back(shoot());
		reload = RELOAD_TIME;
	}
	else { //reload
		reload-=World::speed;
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
		cout << "Current Score: " << player->score << endl;
	}
	
	vector<Enemy>::iterator a = World::enemies.begin();
	vector<Enemy>::iterator b = World::enemies.end();
	
	bool found = false;
	while (a != b && !found) {
		if (a->id == this->id) {
			World::enemies.erase(a);
			World::loadEnemies(1);
			found = true;
		}	
		a++;
	}
}