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

class GameData {
private:
	json gamedata;

	void loadGameData();

public:
	GameData::GameData();

	int numEnemies; // Total number of enemies
	int numWaves; // Total number of waves

	// Textures
	std::string m_playerShipTextureFile;
	std::string m_enemyTextureFile;


	// Enemy spawn positions
	std::vector<sf::Vector2f> enemyWaveVel; // Velocities for enemies in each wave
	std::vector<float> waveSpawnTimes; // Spawn times for enemy waves
	std::vector<sf::Vector2f> enemySpawnPos; // Enemy spawn positions
	std::vector<int> waveSizes;
	std::vector<int> enemyTypes;
};

#endif