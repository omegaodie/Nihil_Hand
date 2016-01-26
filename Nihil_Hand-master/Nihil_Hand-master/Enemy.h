#pragma once
#ifndef __ENEMY_H__
#define ___ENEMY_H__

#include <SFML/Graphics.hpp>
//#include "AnimatedSprite.h"
#include "GameData.h"

//FMOD include 
#pragma comment(lib, "fmod_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"


class Enemy //: public AnimatedSprite
{
private:
	sf::Sprite enemySprites[3];

public:

	const GameData& gd;

	Enemy::Enemy(float x, float y, const GameData &gdata);
	Enemy::Enemy(const GameData &gdata);
	Enemy::Enemy(int mode, const GameData &gdata); int kills;
	Enemy::~Enemy();

	void Enemy::Draw(sf::RenderWindow &w, int mode);

	void Enemy::Init(sf::Clock);
	void Enemy::Init();

	bool* alive;
	bool levelStarted;

	void Enemy::Update(sf::Clock);//return bool if alive or dead, leaving it void for now 
	void Enemy::Update(int mode);
	bool Enemy::FireBullets();
	void Enemy::TrainingEnemies(int enemyType);

	//void Enemy::Animate();

	int* life;

	std::vector<float> enemyWaveStats;
	std::vector<std::vector<float>> enemyWaveVector;

	std::clock_t timeAtLastFire;	// Time the last bullet was shot
	std::clock_t timeNow;			// Current time

	sf::Texture droneTexture;
	sf::Texture droneBulletTexture;
	sf::Texture sweeperTexture;
	sf::Texture sweeperBulletTexture;
	sf::Texture sentryTexture;
	sf::Texture sentryBulletTexture;
	
	sf::Sprite droneSprite;
	sf::Sprite droneBulletSprite;
	sf::Sprite sweeperSprite;
	sf::Sprite sweeperBulletSprite;
	sf::Sprite sentrySprite;
	sf::Sprite sentryBulletSprite;

	std::vector<float> droneOffSet;
	std::vector<sf::Vector2f> droneSideSpd;
	bool droneDir[100]; // Direction a drone is moving. True for right, false for left.
	
	std::vector<sf::Vector2f> enemyPosition;	// Vector of enemy positions
	std::vector<sf::Vector2f> enemyVelocity;	// Vector of enemy velocities
	std::vector<float> enemyWaveSpawns;		// Spawn times for enemy waves
	std::vector<float> enemyHealth;			// Vector of enemy health
	std::vector<int> enemyType;			// Vector of enemy type (0 = Drone, 1 = Sweeper, 2 = Sentry)
	bool enemyAlive[200];	// Vectors of bool isn't working quite right
	int enemiesSpawned;
	int currentWave;	// Wave to be spawned next
	bool wavesSpawn[30];
	int droneHP, sweeperHP, sentryHP, healthTypes[3];
	int enemiesMade;

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