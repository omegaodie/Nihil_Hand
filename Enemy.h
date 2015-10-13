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

	

	sf::Image* e_image;//we load an image from file

	sf::Vector2f* e_location;//where the sprite is positioned

	sf::Sprite* e_sprite;//what gets drawn

	sf::Texture* e_texture;//what we draw on the sprite

	sf::IntRect* e_current_frame;// this is the rectangle we use for the spritesheet

	int timer; //  set with clock and then referenced for frame change

	float e_sprite_counterX, e_sprite_counterY, e_sprite_height, e_sprite_width;//which sprite-sheet cell we are on currently
	// defined by co-ordinates


};

#endif 