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
	std::string m_shipTextureFile;
	std::string m_MenuBackgroundFile;
	std::string m_Button1File;
	std::string m_Button2File;

	//sprite textures
	sf::Texture* m_EnemyTexture;
	sf::Texture* m_PlayerTexture;
	sf::Texture* m_Button1Texture;
	sf::Texture* m_Button2Texture;
	sf::Texture* m_MenuBackgroundTexture;

	// Enemy spawn positions
	float waveOneSpawnTime;
	float waveTwoSpawnTime;
	sf::Vector2f enemySpawnWaveOne[5];
	sf::Vector2f enemySpawnWaveTwo[5];

	bool loaded;
	

};

#endif