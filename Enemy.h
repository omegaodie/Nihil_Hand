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

using namespace std;

class Enemy //: public AnimatedSprite
{
private:
	sf::Sprite enemySprites[3];
	void Enemy::DroneAI(int squad); // AI for drones
	void Enemy::DroneStrafe(int squad); // Moves the drones left and right around their center
	void Enemy::DroneToCenters(int squad); // Moves the drones to their centers

	sf::Vector2f Enemy::NormVec(sf::Vector2f vec); // Normalizes vectors

	int trainingCurrentType; // Current enemy type in training
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

	void Enemy::Update(sf::Clock); //return bool if alive or dead, leaving it void for now 
	void Enemy::Update(int mode);
	bool Enemy::FireBullets();
	void Enemy::TrainingEnemies(int enemyType);
	void Enemy::DroneCentering(int i);

	//void Enemy::Animate();

	int* life;

	vector<float> enemyWaveStats;
	vector<std::vector<float>> enemyWaveVector;

	clock_t timeAtLastFire;	// Time the last bullet was shot
	clock_t timeNow;			// Current time

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

	/////////////////////// VARIABLES FOR THE DRONES ///////////////////////
	vector<float> droneMaxOffSet; // Maximum distance drones can move from their centers
	vector<float> droneDis;	// Distance drones are seperated by
	vector<int> droneGroupSize; // Number of drones in a group
	vector<int> droneGroupAlive; // Number of alive drones in a group
	vector<int> droneGroupPos; // Where a drone is in a group. 0 if it's the first, 1 if it's the second, etc.
	vector<float> droneGroupLength; // Length between one end of a group to the other end
	vector<float> droneGroupSplit; // Distance between drone's in a group when all are alive
	vector<float> droneGroupStart; // Position of the first drone in a group
	vector<int> droneStartDead, droneEndDead; // Drones killed on the two ends of a group
	bool droneCentered[100]; // True = Drone moving around it's center point | False = Drone moving TO it's center point
	vector<float> droneSideSpd; // Speed drones move side to side
	vector<sf::Vector2f> droneCenters; // Center that the drone moves around.
	vector<vector<sf::Vector2f>> droneCentersVec; // Vector of vectors that contain droneCenters. Each vector is for each group of drones
	vector<int> droneFirstEnemy; // Position of the first enemy in a group among all enemies.
	vector<int> droneGroupNum; // Group that a drone is in. If a drone is in the first group, it's 0. 1 if it's the second, etc.
	bool droneDir[100]; // Direction a drone is moving. True for right, false for left.
	bool droneSide[100]; 
	/////////////////////// VARIABLES FOR THE DRONES ///////////////////////
	
	vector<sf::Vector2f> enemyPosition;	// Vector of enemy positions
	vector<sf::Vector2f> enemyVelocity;	// Vector of enemy velocities
	vector<float> enemyWaveSpawns;		// Spawn times for enemy waves
	vector<float> enemyHealth;			// Vector of enemy health
	vector<int> enemyType;				// Vector of enemy type (0 = Drone, 1 = Sweeper, 2 = Sentry)
	bool enemyAlive[200];	// Vectors of bool isn't working quite right
	int enemiesSpawned;
	int currentWave;	// Wave to be spawned next
	bool wavesSpawn[30];
	int droneHP, sweeperHP, sentryHP, healthTypes[3];
	int enemiesMade;

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