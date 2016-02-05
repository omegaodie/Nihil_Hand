#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <memory>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "jsoncons\json.hpp"

using jsoncons::json;
using jsoncons::json_exception;
using jsoncons::pretty_print;
using jsoncons::json_deserializer;
using namespace std;

class GameData {
private:
	json gamedata;

	void loadGameData();

public:
	GameData::GameData();

	int numEnemies; // Total number of enemies
	int numWaves; // Total number of waves

	// Textures
	string m_playerShipTextureFile;
	string m_enemyTextureFile;


	// Enemy spawn positions
	vector<sf::Vector2f> enemyWaveVel; // Velocities for enemies in each wave
	vector<float> waveSpawnTimes; // Spawn times for enemy waves
	vector<sf::Vector2f> enemySpawnPos; // Enemy spawn positions
	vector<int> waveSizes; // Size of each wave
	vector<int> enemyType; // Type of enemy in vector containing all enemies
	vector<int> waveEnemyType; // Type of enemy in a certain wave
	
	int droneWaveNum; // Number of drone waves
	vector<int> droneWaveSizes; // Size of each drone wave
	vector<int> droneSquadSplit; // Default distance between drones in a squad
	vector<float> droneSquadStart; // X-Position of first drone in drone wave
};

#endif