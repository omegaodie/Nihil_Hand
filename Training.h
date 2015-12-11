#pragma once
#ifndef __TRAINING_H__
#define ___TRAINING_H__

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include <istream>
#include <sstream>

// FMOD include

#pragma comment(lib, "fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"

class Training
{
private:
	sf::Texture shopTexture; sf::Sprite shopSprite;
	sf::Vector2f shopAreaPos;

	/*sf::Font shopReturnFont;
	sf::Text returnToShop;*/

	FMOD::System *FMODsys;
	FMOD_RESULT result;
	FMOD::Sound *trainingMusic;
	bool musicPlaying, muteMusic;
	bool muteMusicToggle;
	
public:
	Training::Training();
	Training::~Training();
	void Run(sf::RenderWindow &w, sf::Event &eve);
	void Draw(sf::RenderWindow &w);
	FMOD::Channel *musicChannel;
};

#endif