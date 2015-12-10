#ifndef __PLAYER_H__
#define ___PLAYER_H__

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include "GameData.h"

//using jsoncons::json;
//using jsoncons::json_exception;
//using jsoncons::pretty_print;
//using jsoncons::json_deserializer;

class Player
{
public:
	Player::Player();
	Player::Player(float spawnX, float spawnY, const GameData &gd);
	Player::~Player();
	void Update(sf::RenderWindow &w, POINT p);
	void Draw(sf::RenderWindow &w);
	sf::Vector2f* Player::GetPos();

private:
	const GameData & gd;
	sf::Texture* shipTexture, enemyTexture;
	sf::Sprite* shipSprite, enemySprite;
	sf::Vector2f shipPos, enemyPos[5];
	sf::Vector2f shipVelocity, enemyVelocity[5];
	float shipSpeed, dx, dy, px, py, dlength;
	

};

#endif