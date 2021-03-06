#pragma once
#ifndef __PLAYER_H__
#define ___PLAYER_H__

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include "jsoncons\json.hpp"

using jsoncons::json;
using jsoncons::json_exception;
using jsoncons::pretty_print;
using jsoncons::json_deserializer;

#include "GameData.h"
#include "Shop.h"
#include <istream>
#include <sstream>

class Player
{
public:
	Player::Player();
	Player::Player(float spawnX, float spawnY, float shieldDef, float HP, float speed, float hitBox, int points);
	Player::~Player();
	int playerHealth;
	int playerScore;
	float shipSpeed;
	float dx, dy, px, py, dlength;

	sf::Font shopReturnFont;
	sf::Text returnToShopText; bool drawText;
	
	GameData* gd;
	sf::Texture shipTexture, gameOverTexture;
	sf::Sprite shipSprite, gameOverSprite;
	sf::Vector2f shipPos, enemyPos[5];
	sf::Vector2f shipVelocity, enemyVelocity[5];
	sf::Font HUDFont;
	sf::Text HUDplayerHealth, HUDplayerScore, gameOverText;

	std::string healthString, scoreString;
	
	void Update(sf::RenderWindow &w, POINT p);
	void Draw(sf::RenderWindow &w, int mode);
	void SetStats(std::vector<float>& myStats);
	int state(); int gameMode;
	void ReturnToShop(sf::Event &eve, int mode);
	void QuitGameOver(sf::Event &eve);
	void DrawGameOver(sf::RenderWindow &w);
};

#endif