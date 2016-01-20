#include "GameData.h"

GameData::GameData()
{
	loadGameData();
}

void GameData::loadGameData()
{
	gamedata = json::parse_file("GameData.json");

	json& mGameData = gamedata;

	numEnemies = 0;
	numWaves = 16;

	for (int w = 0; w < numWaves; w++)
	{
		std::stringstream ss;
		ss << w + 1;			// Get current wave to create settings for
		std::string wave = ss.str();
		enemyTypes.push_back(mGameData["level_1"]["wave_" + wave]["enemyType"].as<int>());			// Enemy type in current wave
		waveSizes.push_back(mGameData["level_1"]["wave_" + wave]["enemy"].size());					// Size of current wave	
		numEnemies += mGameData["level_1"]["wave_" + wave]["enemy"].size();							// Add wave size to total number of enemies
		waveSpawnTimes.push_back(mGameData["level_1"]["wave_" + wave]["spawn_time"].as<int>());		// Spawn time of current wave
		enemyWaveVel.push_back(sf::Vector2f(mGameData["level_1"]["wave_" + wave]["velocityX"].as<int>(),	// Velocity of enemies in current wave
			mGameData["level_1"]["wave_" + wave]["velocityY"].as<int>()));
		for (int i = 0; i < waveSizes.at(w); i++)
		{
			enemySpawnPos.push_back(sf::Vector2f(mGameData["level_1"]["wave_" + wave]["enemy"][i]["x"].as<int>(),	
				mGameData["level_1"]["wave_" + wave]["enemy"][i]["y"].as<int>()));		// Spawn positions of current wave
		}
	}
}