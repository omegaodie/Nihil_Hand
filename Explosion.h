#pragma once


#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "GameData.h"

class Explosion
{
public:
	Explosion::Explosion(const GameData &gd);
	Explosion::~Explosion();

	void Explosion::Init(sf::Vector2f vec);

	

	const GameData& gd;

	////for explode at end
	float explosionTimer;
	bool setExplode;
	int currentExplodeFrame;

	//sf::Texture explosionFrames[81];

	sf::Vector2f position;

	sf::Sprite explSprite;

	sf::Clock C;

	bool Explosion::getActive();
	void Explosion::Explode(sf::RenderWindow &w);

};