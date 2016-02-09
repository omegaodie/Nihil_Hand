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

using namespace std;

class GameData {
private:
	json gamedata;

	void loadGameData();

public:
	GameData::GameData();


	int numEnemiesLvLOne;
	int numEnemiesLvLTwo;
	int numEnemiesLvLThree;
	int numWaves;
	int numWavesLvLTwo;
	int numWavesLvLThree;
	// Textures
	std::string m_shipTextureFile;
	std::string m_lvlOneBossTxtFileL;
	std::string m_lvlOneBossTxtFileM;
	std::string m_lvlOneBossTxtFileR;

	std::string m_RocketAnimFile;
	std::string m_SpinningRocket;
	std::string m_RocketFlightFile;

	std::string m_MenuBackgroundFile;
	std::string m_lvl1BackGround;
	std::string m_Button1File;
	std::string m_Button2File;
	std::string m_invincibleFile;
	std::string m_shieldFile;


	//sprite textures
	sf::Texture* m_LvlOneBossRightArmTxt;
	sf::Texture* m_LvlOneBossLeftArmTxt;
	sf::Texture* m_LvlOneBossBodyTxt;

	sf::Texture* m_PlayerInvulnerableTxt;
	sf::Texture* m_PlayerShieldTxt;

	sf::Texture* m_RocketAnimTextures[81];
	sf::Texture* m_RocketFlightTexture;

	sf::Texture* m_PlayerBulletTexture; 
	sf::Texture* m_EnemyBulletTexture;
	sf::Texture* m_EnemyTexture;
	sf::Texture* m_PlayerTexture;
	sf::Texture* m_lvl1BackGroundTexture;
	sf::Texture* m_Button1Texture;
	sf::Texture* m_Button2Texture;
	sf::Texture* m_MenuBackgroundTexture;

	// Enemy spawn positions Level One
	std::vector<sf::Vector2f> enemyWaveVel; // Velocities for enemies in each wave
	std::vector<float> waveSpawnTimesLvLOne; // Spawn times for enemy waves
	std::vector<sf::Vector2f> enemySpawnPosLvLOne; // Enemy spawn positions
	std::vector<int> waveSizesLvLOne;
	std::vector<int> enemyTypesLvLOne;
	std::vector<int> bossWave;

	int droneWaveNum; // Number of drone waves
	vector<int> droneWaveSizes; // Size of each drone wave
	vector<int> droneSquadSplit; // Default distance between drones in a squad
	vector<float> droneSquadStart; // X-Position of first drone in drone wave

	//////////////////////////////////////////////////
	/////////LEVEL TWO/////////////////////////////
	////////////////////////////////////////////////////
	std::vector<float> waveSpawnTimesLvLTwo; // Spawn times for enemy waves
	std::vector<sf::Vector2f> enemySpawnPosLvLTwo; // Enemy spawn positions
	std::vector<int> waveSizesLvLTwo;
	std::vector<int> enemyTypesLvLTwo;
	//////////////////////////////////////////////////
	/////////LEVEL THREE/////////////////////////////
	////////////////////////////////////////////////////
	std::vector<float> waveSpawnTimesLvLThree; // Spawn times for enemy waves
	std::vector<sf::Vector2f> enemySpawnPosLvLThree; // Enemy spawn positions
	std::vector<int> waveSizesLvLThree;
	std::vector<int> enemyTypesLvLThree;






	//player Spawn Location
	sf::Vector2f* playerSpawnLevelOne;
	int BossSpawnTime; 
	int bossType;
	

	//playerBulletEnemy widthshtuff
	sf::Vector2f* m_PlayerDimensions;
	sf::Vector2f* m_EnemyDimensions;
	sf::Vector2f* m_BulletDimensions;


};

#endif