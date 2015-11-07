#include "GameData.h"

GameData::GameData()
{
	loadGameData();
}

void GameData::loadGameData()
{
	gamedata = json::parse_file("GameData.json");

	json& mGameData = gamedata;

	for (int i = 0; i < 5; i++)
	{
		enemySpawnWaveOne[i].x = mGameData["level_1"]["wave_1"]["enemy"][i]["x"].as<int>();
		enemySpawnWaveOne[i].y = mGameData["level_1"]["wave_1"]["enemy"][i]["y"].as<int>();
		enemySpawnWaveTwo[i].x = mGameData["level_1"]["wave_2"]["enemy"][i]["x"].as<int>();
		enemySpawnWaveTwo[i].y = mGameData["level_1"]["wave_2"]["enemy"][i]["y"].as<int>();
	}

	waveOneSpawnTime = mGameData["level_1"]["wave_1"]["spawn_time"].as<int>();
	waveTwoSpawnTime = mGameData["level_1"]["wave_2"]["spawn_time"].as<int>();
}