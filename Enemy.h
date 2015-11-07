#ifndef __ENEMY_H__
#define ___ENEMY_H__

#include <SFML/Graphics.hpp>
//#include "AnimatedSprite.h"
#include "GameData.h"



class Enemy //: public AnimatedSprite
{
public:
	Enemy::Enemy(float x, float y);
	Enemy::Enemy();
	Enemy::~Enemy();

	void Enemy::Draw(sf::RenderWindow &w);

	void Enemy::Init(sf::Clock);
	void Enemy::Init();

	bool* alive;
	bool levelStarted;

	void Enemy::Update(sf::Clock);//return bool if alive or dead, leaving it void for now 
	void Enemy::Update();

	//void Enemy::Animate();

	int* life;

	std::clock_t timeAtLastFire;	// Time the last bullet was shot
	std::clock_t timeNow;			// Current time

	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	sf::Vector2f enemyVelocity[10];
	sf::Vector2f enemyPosition[10];
	GameData* gd;

};

#endif 