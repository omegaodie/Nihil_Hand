#pragma once
#include "stdafx.h"
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
#include "Bullet.h"

class Ship
{
public:
	Ship::Ship();
	Ship::Ship(float x, float y);
	Ship::~Ship();
	sf::Texture shipTexture;
	sf::Sprite shipSprite;
	sf::Vector2f shipPos;
	sf::Vector2f shipVelocity;
	float shipSpeed;
	void Update(sf::RenderWindow &w, POINT p);
	void Draw(sf::RenderWindow &w);
};