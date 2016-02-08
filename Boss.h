#pragma once
#ifndef __BOSS_H__
#define ___BOSS_H__

#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "Rocket.h"

//FMOD include 
#pragma comment(lib, "fmod_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"


class Boss 
{
public:
	Boss::Boss(const GameData &gd);

	virtual void Boss::Init();

	virtual void Boss::Draw(sf::RenderWindow &w);

	virtual void Boss::ArtificialIntelligence();

	virtual void Boss::FireBullets();


protected:
	int* life;

	const GameData& gd;

	std::clock_t timeAtLastFire;	// Time the last bullet was shot
	std::clock_t timeNow;			// Current time


	sf::Texture* bBulletTexture;
	sf::Sprite* bBulletSprite;

	sf::Vector2f* bVelocity;
	sf::Vector2f* bPosition;

	int bHealth;
	bool bAlive;


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