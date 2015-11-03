#ifndef __ENEMY_H__
#define ___ENEMY_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/System/Clock.hpp>

class Enemy
{
public:
	Enemy(float x, float y);
	~Enemy();


	void Enemy::Draw(sf::RenderWindow &w);

	void Enemy::Move();

	/*bool*/void Enemy::Update();//return bool if alive or dead, leaving it void for now 

	int* life;

	sf::Vector2f* location;

	bool* alive;  

};

#endif 