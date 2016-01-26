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


	int numEnemies;
	int numWaves;
	// Textures
	std::string m_shipTextureFile;
	std::string m_lvlOneBossTxtFileL;
	std::string m_lvlOneBossTxtFileM;
	std::string m_lvlOneBossTxtFileR;

	std::string m_RocketAnimFile;
	std::string m_RocketFlightFile;

	std::string m_MenuBackgroundFile;
	std::string m_lvl1BackGround;
	std::string m_Button1File;
	std::string m_Button2File;


	//sprite textures
	sf::Texture* m_LvlOneBossRightArmTxt;
	sf::Texture* m_LvlOneBossLeftArmTxt;
	sf::Texture* m_LvlOneBossBodyTxt;

	sf::Texture* m_RocketAnimTextures[6];
	sf::Texture* m_RocketFlightTexture;

	sf::Texture* m_PlayerBulletTexture; 
	sf::Texture* m_EnemyBulletTexture;
	sf::Texture* m_EnemyTexture;
	sf::Texture* m_PlayerTexture;
	sf::Texture* m_lvl1BackGroundTexture;
	sf::Texture* m_Button1Texture;
	sf::Texture* m_Button2Texture;
	sf::Texture* m_MenuBackgroundTexture;

	// Enemy spawn positions
	std::vector<sf::Vector2f> enemyWaveVel; // Velocities for enemies in each wave
	std::vector<float> waveSpawnTimes; // Spawn times for enemy waves
	std::vector<sf::Vector2f> enemySpawnPos; // Enemy spawn positions
	std::vector<int> waveSizes;
	std::vector<int> enemyTypes;
	std::vector<int> bossWave;


	//player Spawn Location
	sf::Vector2f* playerSpawnLevelOne;
	

	//playerBulletEnemy widthshtuff
	sf::Vector2f* m_PlayerDimensions;
	sf::Vector2f* m_EnemyDimensions;
	sf::Vector2f* m_BulletDimensions;


};

#endif