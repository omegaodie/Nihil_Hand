#include "Enemy.h"

Enemy::Enemy(float x, float y){
	location = new sf::Vector2f(x, y);

}

void Enemy::Draw(sf::RenderWindow &w){
	sf::CircleShape shape;
	shape.setRadius(40.f);
	shape.setPosition(100.f, 100.f);
	shape.setFillColor(sf::Color::Cyan);
	w.draw(shape);
}


void Enemy::Update(){
	location->x += 5;
	location->y += 5;
}