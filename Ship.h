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

class Ship
{
public:
	Ship::Ship();
	Ship::Ship(float x, float y);
	Ship::~Ship();
	sf::Texture shipTexture; // yo thomas Private man class variables need to be private
	sf::Sprite shipSprite; // you can blame Daire for me fuckin wit ur work
	sf::Vector2f shipPos;  //im code reviewing ;)
	sf::Vector2f shipVelocity;
	float shipSpeed;
	void Update(sf::RenderWindow &w);
	void Draw(sf::RenderWindow &w);
	void FireBullet();
	sf::Vector2f GetShipPos();
};
