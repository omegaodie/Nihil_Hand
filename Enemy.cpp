#include "Enemy.h"

Enemy::Enemy(float x, float y){
	e_location = new sf::Vector2f(x, y);
	
}

void Enemy::Init(sf::Clock c){
	e_image = new sf::Image();
	e_texture = new sf::Texture();
	e_sprite = new sf::Sprite();
	e_current_frame = new sf::IntRect();
	e_image->loadFromFile("resources/runningcat.png");
	e_sprite_counterX = 0;
	e_sprite_counterY = 0;
	timer = c.getElapsedTime().asMilliseconds();

}

void Enemy::Draw(sf::RenderWindow &w){// animateion logic here
	e_sprite->setTexture(*e_texture, true);
	w.draw(*e_sprite);
}


void Enemy::Update(sf::Clock c){
	
	if (timer + 80 < c.getElapsedTime().asMilliseconds()){
		timer = c.getElapsedTime().asMilliseconds();
		if (e_sprite_counterX < 1){
			e_sprite_counterX++;
		}
		else{
			e_sprite_counterX = 0;
			if (e_sprite_counterY < 2){
				e_sprite_counterY++;
			}
			else{
				e_sprite_counterY = 0;
			}
		}
	}
	Animate();
	e_texture->loadFromImage(*e_image, *e_current_frame);
}

void Enemy::Animate(){

	e_current_frame = new sf::IntRect(e_sprite_counterX * 512, e_sprite_counterY * 256, 512, 256);
}