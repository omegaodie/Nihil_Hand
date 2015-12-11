#pragma once
#ifndef __ENEMY_H__
#define ___ENEMY_H__

#include <SFML/Graphics.hpp>
//#include "AnimatedSprite.h"
#include "GameData.h"

//FMOD include 
#pragma comment(lib, "fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"


class Enemy //: public AnimatedSprite
{
public:
	Enemy::Enemy(float x, float y);
	Enemy::Enemy();
	Enemy::Enemy(int mode); int kills;
	Enemy::~Enemy();

	void Enemy::Draw(sf::RenderWindow &w, int mode);

	void Enemy::Init(sf::Clock);
	void Enemy::Init();

	bool* alive;
	bool levelStarted;

	void Enemy::Update(sf::Clock);//return bool if alive or dead, leaving it void for now 
	void Enemy::Update(int mode);
	bool Enemy::FireBullets();

	//void Enemy::Animate();

	int* life;

	std::clock_t timeAtLastFire;	// Time the last bullet was shot
	std::clock_t timeNow;			// Current time

	sf::Texture enemyTexture;
	sf::Texture enemyBulletTexture;
	sf::Sprite enemySprite;
	sf::Sprite enemyBulletSprite;
	sf::Vector2f enemyVelocity[10];
	sf::Vector2f enemyPosition[10];
	int enemyHealth[10];
	bool enemyAlive[10];

	GameData* gd; 

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
	FMOD::Reverb *reverb;
		
};

#endif 