#pragma once
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

class Collision
{
private:
	

	Bullet* myBullets;
	Enemy* myEnemies;
	Player* myPlayer;
	float playerDmg;
public:
	Collision::Collision();
	Collision::Collision(Enemy* enemies, Bullet* bullets, Player* player, float playerDamage);
	Collision::~Collision();

	void Collision::CheckForCollision();
	bool Collision::EnemyFiring();

	
};