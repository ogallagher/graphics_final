/*

Owen Gallagher, Brian Park
4 May 2019
Computer Graphics

enemy.h

*/

#ifndef ENEMY_H
#define ENEMY_H

//local includes
#include "../include/person.h"
#include "../include/player.h"
#include "../include/bullet.h"

class Enemy : public Person {
public:
	static Player *player; //pointer to player for easy access
	static const int RELOAD_TIME; //max time to spend reloading
	static const int FOV; //field of view (halved)
	
	int reload; //time currently spent reloading
	int standTime; //max time to spend standing
	float stand; //time currently spent standing
	bool standing; //is currently standing (initially false)
	ovector destination; //current movement target (often player->location)
	
	Enemy(int *rx, int *ry);
	static void loadPlayer(Player *);
	void followControl();
	void shootControl();
	Bullet shoot(); //extend Person::shoot()
	void stay();
	void die(bool goodBullet);
};

#endif