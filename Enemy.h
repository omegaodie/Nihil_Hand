#ifndef __ENEMY_H__
#define ___ENEMY_H__

#include <SFML/Graphics.hpp>
//#include "AnimatedSprite.h"
#include "GameData.h"
#include "Bullet.h"



class Enemy //: public AnimatedSprite
{
public:
	Enemy::Enemy(float x, float y);
	Enemy::Enemy();
	Enemy::~Enemy();

	void Enemy::Draw(sf::RenderWindow &w);

	void Enemy::Init(sf::Clock);
	void Enemy::Init();



	void Enemy::Update(sf::Clock);//return bool if alive or dead, leaving it void for now 
	void Enemy::Update();
	bool Enemy::FireBullets();
	void Enemy::HitDetection();

	//void Enemy::Animate();
private:
	int* life;
	bool* alive;
	bool levelStarted;

	std::clock_t timeAtLastFire;	// Time the last bullet was shot
	std::clock_t timeNow;			// Current time

	sf::Texture* enemyTexture;
	sf::Texture* enemyBulletTexture;
	sf::Sprite* enemySprite;
	sf::Sprite* enemyBulletSprite;
	sf::Vector2f enemyVelocity[10];
	sf::Vector2f enemyPosition[10];
	bool enemyAlive[10];

	GameData* gd; 
	Bullet* bullet;

};

#endif 