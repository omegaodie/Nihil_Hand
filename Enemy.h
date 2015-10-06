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

	void Enemy::Init(sf::Clock);

	bool* alive;

	/*bool*/void Enemy::Update(sf::Clock);//return bool if alive or dead, leaving it void for now 

	void Enemy::Animate();

	int* life;

	

	sf::Image* e_image;//e for enemy

	sf::Vector2f* e_location;

	sf::Sprite* e_sprite;

	sf::Texture* e_texture;

	sf::IntRect* e_current_frame;

	int timer;

	float e_sprite_counterX, e_sprite_counterY;


};

#endif 