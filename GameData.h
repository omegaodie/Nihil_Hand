#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <memory>
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

	// Textures
	std::string m_playerShipTextureFile;
	std::string m_enemyTextureFile;

	// Enemy spawn positions
	float waveOneSpawnTime;
	float waveTwoSpawnTime;
	sf::Vector2f enemySpawnWaveOne[5];
	sf::Vector2f enemySpawnWaveTwo[5];
	

};

#endif