#ifndef __ENEMY_H__
#define ___ENEMY_H__

#include <SFML/Graphics.hpp>


class Enemy
{
public:
	Enemy::Enemy(float x, float y);
	Enemy::~Enemy();


	void Enemy::Draw(sf::RenderWindow &w);

	void Enemy::Move();

	/*bool*/void Enemy::Update();//return bool if alive or dead, leaving it void for now 

	int* life;

	sf::Vector2f* location;

	bool* alive;  

};

#endif 