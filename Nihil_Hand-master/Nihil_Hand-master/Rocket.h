#pragma once
#ifndef __ROCKET_H__
#define __ROCKET_H__

#include <SFML/Graphics.hpp>
#include "GameData.h"

//FMOD include 
#pragma comment(lib, "fmod_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"


class Rocket
{
public:
	Rocket::Rocket(const GameData &gdata);

	void Rocket::Init(sf::Vector2f*, int);

	void Rocket::Draw(sf::RenderWindow &w);

	void Rocket::update();
	void Rocket::Animate();

	bool getAlive();

	int fireType;

	const GameData& gd;

	sf::Clock time;			// Current time

	float timeAtFired, deltaTime;

	sf::Texture* rExplosionTextures[6];
	sf::Texture* rFlightTexture;
	sf::Sprite* rSprite;

	float r_Theta;
	float r_CurrentRadius;
	float r_PosOnRadius;
	int frame, incrementA, incrementB, dieSwitch;
						
	sf::Vector2f* rVelocity;
	sf::Vector2f* rPosition;
	sf::Vector2f* actualLocation;

	bool rAlive;


	FMOD::System *FMODsys;
	FMOD_RESULT result;
	FMOD::Sound *enemyHum, *testMusic;
	bool musicPlaying, enemyHumPlaying, muteMusic, muteReverb, mute3DSound;
	bool muteMusicToggle, muteReverbToggle, mute3DSoundToggle;
	FMOD::Channel *channel;
	FMOD::Channel *musicChannel;

	FMOD_VECTOR pos;
	FMOD_VECTOR vel;
	FMOD_REVERB_PROPERTIES prop1;
	FMOD::Reverb3D *reverb;
};

#endif 