#ifndef __ENEMY_H__
#define ___ENEMY_H__

using namespace std;

#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "Bullet.h"



class Enemy 
{
public:


	Enemy::Enemy(const GameData &gd, int i);
	Enemy::~Enemy();

	void Enemy::Draw(sf::RenderWindow &w);

	void Enemy::Init(sf::Clock);
	void Enemy::Init();

	sf::Vector2f* Enemy::GetPos();


	void Enemy::Update(sf::Clock);//return bool if alive or dead, leaving it void for now 
	void Enemy::FireBullets();

	//void Enemy::Animate();
private:
	int* life;
	bool* alive;
	bool levelStarted;

	Bullet* theBullets;

	sf::Int32 timeAtLastFire;	// Time the last bullet was shot
	sf::Int32 timeNow;			// Current time

	sf::Texture* enemyTexture;
	sf::Sprite* enemySprite;
	sf::Vector2f enemyVelocity;
	sf::Vector2f enemyPosition;
	bool enemyAlive;

	const GameData& gd; 

};

#endif 