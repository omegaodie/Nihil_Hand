#ifndef __ENEMY_H__
#define ___ENEMY_H__

#include <SFML/Graphics.hpp>
//#include "AnimatedSprite.h"



class Enemy //: public AnimatedSprite
{
public:
	Enemy::Enemy(/*float x, float y*/);
	Enemy::~Enemy();

	/*void Enemy::Draw(sf::RenderWindow &w);

	void Enemy::Init(sf::Clock);

	bool* alive;*/

	/*bool*///void Enemy::Update(sf::Clock);//return bool if alive or dead, leaving it void for now 

	//void Enemy::Animate();

	//int* life;

};

#endif 