/*

Owen Gallagher, Brian Park
17 April 2019
Computer Graphics

world.cpp

*/

//core headers
#include <vector>
#include <random>

//local headers
#include "../include/world.h"
#include "../include/camera.h"
#include "../include/matrixutils.h"
#include "../include/enemy.h"
#include "../include/obstacle.h"
#include "../include/light.h"
#include "../include/material.h"
#include "../include/room.h"

int World::dimsWindow[2] = {600,600};
int World::dimsFOV[3] = {600,600,600};
int World::dims[3] = {200,10,200};
double World::t = 0;
double World::speed = 1;
double World::fastSpeed = 1;
double World::slowSpeed = 1;
double World::osSpeed = 1;
float World::mouse[2] = {0,0};
ovector World::pointer;
ovector World::cursor;
bool World::clicked = false;
bool World::keyW = false;
bool World::keyD = false;
bool World::keyS = false;
bool World::keyA = false;
bool World::keyWalk = false;

Camera *World::camera = new Camera();
Light *World::light = new Light();
Player *World::player = new Player();
random_device World::randomCore;
uniform_real_distribution<float> World::randomizer(0.0,1.0);

Room **World::rooms;
vector<Bullet*> World::bullets;
vector<Obstacle*> World::obstacles;
vector<Enemy*> World::enemies;

const int World::EYE_NEAR = World::dimsFOV[2]/20;
const int World::CURSOR_HEIGHT = Person::dimsTorso[1];
const int World::ROOMS_RENDERED = 3; //render 3x3 square at a time (odd number)
const int World::ROOMS_ALL = 7; //keep a 7x7 grid in memory (odd number)

float World::pmatrix[16],World::mvmatrix[16],World::pmvmatrix[16],World::umatrix[16];

void World::init() {
	cout << "init light" << endl;
	light->material.setColor(1,1,1); //white light
	light->material.setADS(0.9,0.7,0.85);
	
	cout << "init obstacle materials" << endl;
	Obstacle::material.setColor(0.5,0.5,0.5);
	Obstacle::material.setADS(0.5,0.7,0.7);
	
	cout << "init bullet materials" << endl;
	Bullet::material.setColor(0,1,0);
	Bullet::material.setADS(1,0,0);
	
	cout << "init rooms matrix" << endl;
	rooms = new Room*[ROOMS_ALL];
	for (int y=0; y<ROOMS_ALL; y++) {
		rooms[y] = new Room[ROOMS_ALL];
	}
}

void World::reset() {
	cout << "reset player" << endl;
	player->location.set(0,0,0);
	player->reload = 0;
	player->score = 0;
	
	cout << "focus camera on player" << endl;
	camera->loadTarget(&(player->location));
	
	cout << "focus light on player" << endl;
	light->loadTarget(&(player->location));
	
	cout << "clear obstacles" << endl;
	obstacles.clear();
	
	cout << "clear enemies" << endl;
	enemies.clear();
	
	cout << "load rooms" << endl;
	for (int y=0; y<ROOMS_ALL; y++) {		
		for (int x=0; x<ROOMS_ALL; x++) {
			loadRoom(x,y);
		}
	}
}

void World::loadOSSpeed(float osSpeed) {
	World::osSpeed = osSpeed;
	speed *= osSpeed;
	fastSpeed = 1;
	slowSpeed = 0.05;
}

void World::loadCamera() {
	gluLookAt(camera->location.x,camera->location.y,camera->location.z,
			  camera->target->x,camera->target->y,camera->target->z,
			  0,1,0);
}

void World::loadLight(int lightId) {
	float position[3] = {
		light->location.x,
		light->location.y,
		light->location.z
	};
	
	glLightfv(lightId , GL_POSITION , position);
	glLightfv(lightId , GL_AMBIENT , light->material.ambient);
	glLightfv(lightId , GL_DIFFUSE , light->material.diffuse);
	glLightfv(lightId , GL_SPECULAR , light->material.specular);
}

void World::loadMaterial(Material *material) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
}

void World::loadRoom(int rx, int ry) {
	//modify room in array
	Room *room = &(rooms[ry][rx]);
	room->id[0] = rx;
	room->id[1] = ry;
	room->rx = rx * Room::DIM_MAX;
	room->ry = ry * Room::DIM_MAX;
	
	int *rxptr = &(room->rx);
	int *ryptr = &(room->ry);
	int x,y,w,d;
	
	room->clear();
	
	//create obstacles
	w = (Room::WALL_DIM_MAX-Obstacle::DIM_MIN) * getRandom() + Obstacle::DIM_MIN;
	d = Obstacle::DIM_MIN;
	x = 0;
	y = -dims[0]/2 - Obstacle::DIM_MIN/2;
	Obstacle *wallN = new Obstacle(rxptr,ryptr,x,y,w,d);
	obstacles.push_back(wallN);
	room->obstacles.push_back(wallN);
	
	d = Room::WALL_DIM_MAX * getRandom() + Obstacle::DIM_MIN;
	w = Obstacle::DIM_MIN;
	x = dims[0]/2 + Obstacle::DIM_MIN/2;
	y = Obstacle::DIM_MIN;
	Obstacle *wallE = new Obstacle(rxptr,ryptr,x,y,w,d);
	obstacles.push_back(wallE);
	room->obstacles.push_back(wallE);
	
	w = (dims[0] - Obstacle::DIM_MIN)/2;
	for (int i=0; i < Room::PILLARS * getRandom(); i++) {
		x = 2.0 * getRandom() * w - w;
		y = 2.0 * getRandom() * w - w;
		
		Obstacle *pillar = new Obstacle(rxptr,ryptr,x,y,Obstacle::DIM_MIN,Obstacle::DIM_MIN);
		
		obstacles.push_back(pillar);
		room->obstacles.push_back(pillar);
	}
	
	int rw = (dims[0] - Obstacle::DIM_MIN)/2;
	for (int i=0; i < Room::BARRIERS * getRandom(); i++) {
		x = 2.0 * getRandom() * rw - rw;
		y = 2.0 * getRandom() * rw - rw;
		w = Room::PILLAR_DIM_MAX * getRandom();
		d = Room::PILLAR_DIM_MAX * getRandom();
		
		Obstacle *barrier = new Obstacle(rxptr,ryptr,x,y,w,d);
		
		obstacles.push_back(barrier);
		room->obstacles.push_back(barrier);
	}
	
	//create initial enemies
	int numEnemies = rx+ry;
	w = dims[0] - Obstacle::DIM_MIN;
	for (int i=0; i<numEnemies; i++) {
		x = w*getRandom() - w/2;
		y = w*getRandom() - w/2;

		Enemy *enemy = new Enemy(rxptr,ryptr);
		enemy->location.set(x,0,y);
		enemies.push_back(enemy);
		room->enemies.push_back(enemy);
	}
}

void World::display() {
	loadCamera();
	loadLight(GL_LIGHT0);
	
	int dist = floor(ROOMS_RENDERED/2);
	for (int y=Player::roomY-dist; y<=Player::roomY+dist; y++) {
		for (int x=Player::roomX-dist; x<=Player::roomX+dist; x++) {
			rooms[roomIndex(y)][roomIndex(x)].display(x,y);
		}
	}
}

string World::describe() {
	string description = "World: [\n" 
						+ to_string(dims[0]) + "," 
						+ to_string(dims[1]) + ","
						+ to_string(dims[2]) + "] speed="
						+ to_string(speed) + "\nobstacles=[";
	
	vector<Obstacle*>::iterator oit;
	for (oit=obstacles.begin(); oit!=obstacles.end(); oit++) {
		description += (*oit)->describe() + "\n";
	}
	description += "]";
	
	return description;
}

void World::tick() {
	if(keyWalk) {
		speed = fastSpeed * osSpeed;
	}
	else {
		speed = slowSpeed * osSpeed;
	}
	t += 0.001*speed;
}

void World::updateMouse(int x, int y) {
	mouse[0] = 2 * x / (float)dimsWindow[0] - 1; //-1 = left, 1 = right
	mouse[1] = 1 - (2 * y / (float)dimsWindow[1]); //-1 = bottom, 1 = top
}

/*
Adapted from lessons on ray tracing and 3d intersection: 
http://antongerdelan.net/opengl/raycasting.html
Anton Gerdelan 2016

And from GLU:
https://www.khronos.org/opengl/wiki/GluProject_and_gluUnProject_code
*/
void World::updateCursor() {
	//pointer in screen coordinates
	pointer.set(mouse[0],mouse[1],-1,1);
	
	//update projection and modelview matrices
	glGetFloatv(GL_PROJECTION_MATRIX,pmatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX,mvmatrix);
	
	//calculate unprojection matrix
	matrixutils::mult(pmatrix,mvmatrix,pmvmatrix);
	matrixutils::invert(pmvmatrix,umatrix);
	
	//unproject 2d mouse to get 3d pointer
	pointer.applyMatrix(umatrix);
	
	//perspective division
	pointer.w = 1/pointer.w;
	pointer.x *= pointer.w;
	pointer.y *= pointer.w;
	pointer.z *= pointer.w;
	
	//convert to normalized ray
	pointer.sub(&(camera->location));
	pointer.norm();
	
	//ground intersection point
	float d = (CURSOR_HEIGHT - camera->location.y) / pointer.y;
	cursor.set(&pointer);
	cursor.mult(d);
	cursor.add(&(camera->location));
}

void World::drawCursor() {
	glPushMatrix();
	
	loadMaterial(&Bullet::material);
	glTranslatef(cursor.x,cursor.y,cursor.z);
	glutSolidCube(1);
	
	glPopMatrix();
}

float World::getRandom() {
	return randomizer(randomCore);
}

int World::roomIndex(int i) {
	if (i < 0) {
		i = (ROOMS_ALL + (i % -ROOMS_ALL)) % ROOMS_ALL;
	}
	else {
		i = i % ROOMS_ALL;
	}
	
	return i;
}