#pragma once
#ifndef __TRAINING_H__
#define ___TRAINING_H__

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include <istream>
#include <sstream>

#include "Enemy.h"
// FMOD include

#pragma comment(lib, "fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"

class Training
{
private:
	Enemy* myEnemy;
	sf::Texture shopTexture, arrowLeftTexture, arrowRightTexture, 
		testFloorTexture, wallDownTexture, wallUpTexture, droneTexture, sweeperTexture, sentryTexture;
	sf::Sprite shopSpr, arrowLeftSpr, arrowRightSpr, 
		testFloorSpr, wallDownSpr, wallUpSpr, droneSpr, sweeperSpr, sentrySpr, enemyDisplaySpr[3];
	sf::Vector2f shopAreaPos;

	/*sf::Font shopReturnFont;
	sf::Text returnToShop;*/

	FMOD::System *FMODsys;
	FMOD_RESULT result;
	FMOD::Sound *trainingMusic;
	bool musicPlaying, muteMusic;
	bool muteMusicToggle;
	
public:
	Training::Training(Enemy* enemy);
	Training::~Training();
	void Run(sf::RenderWindow &w, sf::Event &eve);
	void Draw(sf::RenderWindow &w);
	FMOD::Channel *musicChannel;
	sf::Vector2f arrowLeftPos, arrowRightPos;
	int currentEnemy;
	float leftHits, rightHits;
};

#endif