#include "GameData.h"

GameData::GameData()
{
	loadGameData();
}

void GameData::loadGameData()
{
	m_EnemyTexture = new sf::Texture();
	m_PlayerTexture = new sf::Texture();
	m_Button1Texture = new sf::Texture();
	m_Button2Texture = new sf::Texture();
	m_lvl1BackGroundTexture = new sf::Texture();
	m_MenuBackgroundTexture = new sf::Texture();
	m_EnemyBulletTexture = new sf::Texture();
	m_PlayerBulletTexture = new sf::Texture();
	m_RocketFlightTexture = new sf::Texture();
	m_LvlOneBossBodyTxt = new sf::Texture();
	//m_RocketTexture = new sf::Texture();
	m_LvlOneBossLeftArmTxt = new sf::Texture();
	m_LvlOneBossRightArmTxt = new sf::Texture();
	m_PlayerInvulnerableTxt = new sf::Texture();
	m_PlayerShieldTxt = new sf::Texture();
	gamedata = json::parse_file("GameData.json");

	json& mGameData = gamedata;

	numEnemiesLvLOne = 0;
	numEnemiesLvLTwo = 0;
	numEnemiesLvLThree = 0;
	numWaves = 16;
	numWavesLvLTwo = 16;
	numWavesLvLThree = 5;
	//////////LEVELONE///////////////////////////////
	for (int w = 0; w < numWaves; w++)
	{
		std::stringstream ss;
		ss << w + 1;			// Get current wave to create settings for
		std::string wave = ss.str();
		enemyTypesLvLOne.push_back(mGameData["level_1"]["wave_" + wave]["enemyType"].as<int>());			// Enemy type in current wave
		waveSizesLvLOne.push_back(mGameData["level_1"]["wave_" + wave]["enemy"].size());					// Size of current wave	
		numEnemiesLvLOne += mGameData["level_1"]["wave_" + wave]["enemy"].size();							// Add wave size to total number of enemies
		waveSpawnTimesLvLOne.push_back(mGameData["level_1"]["wave_" + wave]["spawn_time"].as<int>());		// Spawn time of current wave
		enemyWaveVel.push_back(sf::Vector2f(mGameData["level_1"]["wave_" + wave]["velocityX"].as<int>(),	// Velocity of enemies in current wave
			mGameData["level_1"]["wave_" + wave]["velocityY"].as<int>()));
		for (int i = 0; i < waveSizesLvLOne.at(w); i++)
		{
			enemySpawnPosLvLOne.push_back(sf::Vector2f(mGameData["level_1"]["wave_" + wave]["enemy"][i]["x"].as<int>(),
				mGameData["level_1"]["wave_" + wave]["enemy"][i]["y"].as<int>()));		// Spawn positions of current wave
		}
	}
	for (int i = 0; i < 4; i++) {
		//bossWave.push_back(mGameData["level_1"]["boss_wave"][i][i].as<int>());
	}
	////////////////////LEVELTWO/////////////////////////////////////////////
	for (int w = 0; w < numWavesLvLTwo; w++)
	{
		std::stringstream ss;
		ss << w + 1;			// Get current wave to create settings for
		std::string wave = ss.str();
		enemyTypesLvLTwo.push_back(mGameData["level_2"]["wave_" + wave]["enemyType"].as<int>());			// Enemy type in current wave
		waveSizesLvLTwo.push_back(mGameData["level_2"]["wave_" + wave]["enemy"].size());					// Size of current wave	
		numEnemiesLvLTwo += mGameData["level_2"]["wave_" + wave]["enemy"].size();							// Add wave size to total number of enemies
		waveSpawnTimesLvLTwo.push_back(mGameData["level_2"]["wave_" + wave]["spawn_time"].as<int>());		// Spawn time of current wave
		enemyWaveVel.push_back(sf::Vector2f(mGameData["level_2"]["wave_" + wave]["velocityX"].as<int>(),	// Velocity of enemies in current wave
			mGameData["level_2"]["wave_" + wave]["velocityY"].as<int>()));
		for (int i = 0; i < waveSizesLvLTwo.at(w); i++)
		{
			enemySpawnPosLvLTwo.push_back(sf::Vector2f(mGameData["level_2"]["wave_" + wave]["enemy"][i]["x"].as<int>(),
				mGameData["level_2"]["wave_" + wave]["enemy"][i]["y"].as<int>()));		// Spawn positions of current wave
		}
	}
	////////////////////LEVELTHREE/////////////////////////////////////////////
	for (int w = 0; w < numWavesLvLThree; w++)
	{
		std::stringstream ss;
		ss << w + 1;			// Get current wave to create settings for
		std::string wave = ss.str();
		enemyTypesLvLThree.push_back(mGameData["level_3"]["wave_" + wave]["enemyType"].as<int>());			// Enemy type in current wave
		waveSizesLvLThree.push_back(mGameData["level_3"]["wave_" + wave]["enemy"].size());					// Size of current wave	
		numEnemiesLvLThree += mGameData["level_3"]["wave_" + wave]["enemy"].size();							// Add wave size to total number of enemies
		waveSpawnTimesLvLThree.push_back(mGameData["level_3"]["wave_" + wave]["spawn_time"].as<int>());		// Spawn time of current wave
		enemyWaveVel.push_back(sf::Vector2f(mGameData["level_3"]["wave_" + wave]["velocityX"].as<int>(),	// Velocity of enemies in current wave
			mGameData["level_3"]["wave_" + wave]["velocityY"].as<int>()));
		for (int i = 0; i < waveSizesLvLThree.at(w); i++)
		{
			enemySpawnPosLvLThree.push_back(sf::Vector2f(mGameData["level_3"]["wave_" + wave]["enemy"][i]["x"].as<int>(),
				mGameData["level_3"]["wave_" + wave]["enemy"][i]["y"].as<int>()));		// Spawn positions of current wave
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////
	///GAME 
	/////////////////////////////////////////////////////////////////////////////
	//enemy and player sprite sheet
	m_shipTextureFile = mGameData["level_1"]["textures"]["enemy_texture"]["t"].as_string();
	m_shieldFile = mGameData["level_1"]["textures"]["player_shield_texture"]["t"].as_string();
	m_invincibleFile = mGameData["level_1"]["textures"]["player_invuln_texture"]["t"].as_string();
	m_lvl1BackGround = mGameData["level_1"]["textures"]["lvl_1_texture"]["t"].as_string();

	m_lvl1BackGroundTexture->loadFromFile(m_lvl1BackGround,
		sf::IntRect(int(mGameData["level_1"]["textures"]["lvl_1_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["textures"]["lvl_1_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["textures"]["lvl_1_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["lvl_1_texture"]["h"].as<int>())));

	/////////////Rocket///////////////////////////////////////////////
	m_RocketAnimFile = mGameData["level_1"]["textures"]["rocket_anim__texture"]["t"].as_string();
	m_RocketFlightFile = mGameData["level_1"]["textures"]["rocket_flight_texture"]["t"].as_string();


	for (int i = 0; i < 81; i++) {
		m_RocketAnimTextures[i] = new sf::Texture();
		if (i < 9) {
			m_RocketAnimTextures[i]->loadFromFile(m_RocketAnimFile,
				sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()) * i,
					0,
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()),
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["h"].as<int>())));
		}
		else if(i < 18) {
			m_RocketAnimTextures[i]->loadFromFile(m_RocketAnimFile,
				sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()) * (i - 9),
					100,
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()),
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["h"].as<int>())));
		}
		else if (i < 27) {
			m_RocketAnimTextures[i]->loadFromFile(m_RocketAnimFile,
				sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()) * (i - 18),
					200,
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()),
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["h"].as<int>())));
		}
		else if (i < 36) {
			m_RocketAnimTextures[i]->loadFromFile(m_RocketAnimFile,
				sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()) * (i - 27),
					300,
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()),
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["h"].as<int>())));
		}
		else if (i < 45) {
			m_RocketAnimTextures[i]->loadFromFile(m_RocketAnimFile,
				sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()) * (i - 36),
					400,
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()),
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["h"].as<int>())));
		}
		else if (i < 54) {
			m_RocketAnimTextures[i]->loadFromFile(m_RocketAnimFile,
				sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()) * (i - 45),
					500,
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()),
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["h"].as<int>())));
		}
		else if (i < 63) {
			m_RocketAnimTextures[i]->loadFromFile(m_RocketAnimFile,
				sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()) * (i - 54),
					600,
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()),
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["h"].as<int>())));
		}
		else if (i < 72) {
			m_RocketAnimTextures[i]->loadFromFile(m_RocketAnimFile,
				sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()) * (i - 64),
					700,
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()),
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["h"].as<int>())));
		}
		else if (i < 81) {
			m_RocketAnimTextures[i]->loadFromFile(m_RocketAnimFile,
				sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()) * (i - 72),
					800,
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["w"].as<int>()),
					int(mGameData["level_1"]["textures"]["rocket_anim__texture"]["h"].as<int>())));
		}
	}

	m_RocketFlightTexture->loadFromFile(m_RocketFlightFile,
		sf::IntRect(int(mGameData["level_1"]["textures"]["rocket_flight_texture"]["x"].as<int>()),
			int(mGameData["level_1"]["textures"]["rocket_flight_texture"]["y"].as<int>()),
			int(mGameData["level_1"]["textures"]["rocket_flight_texture"]["w"].as<int>()),
			int(mGameData["level_1"]["textures"]["rocket_flight_texture"]["h"].as<int>())));


	BossSpawnTime = mGameData["level_1"]["Boss"]["spawn_time"].as<int>();
	bossType = mGameData["level_1"]["Boss"]["type"].as<int>();

	//player stuff
	m_PlayerTexture->loadFromFile(m_shipTextureFile,
		sf::IntRect(int(mGameData["level_1"]["textures"]["player_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["textures"]["player_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["textures"]["player_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["player_texture"]["h"].as<int>())));

	m_PlayerBulletTexture->loadFromFile(m_shipTextureFile, 
		sf::IntRect(int(mGameData["level_1"]["textures"]["player_bullet"]["x"].as<int>()),
		int(mGameData["level_1"]["textures"]["player_bullet"]["y"].as<int>()),
		int(mGameData["level_1"]["textures"]["player_bullet"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["player_bullet"]["h"].as<int>())));

	///enemy stuff 
	m_EnemyTexture->loadFromFile(m_shipTextureFile,
		sf::IntRect(int(mGameData["level_1"]["textures"]["enemy_texture"]["x"].as<int>()), 
		int(mGameData["level_1"]["textures"]["enemy_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["textures"]["enemy_texture"]["w"].as<int>()), 
		int(mGameData["level_1"]["textures"]["enemy_texture"]["h"].as<int>())));

	m_EnemyBulletTexture->loadFromFile(m_shipTextureFile,
		sf::IntRect(int(mGameData["level_1"]["textures"]["enemy_bullet"]["x"].as<int>()),
		int(mGameData["level_1"]["textures"]["enemy_bullet"]["y"].as<int>()),
		int(mGameData["level_1"]["textures"]["enemy_bullet"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["enemy_bullet"]["h"].as<int>())));


	//////////////////////////////Boss
	m_lvlOneBossTxtFileR = mGameData["level_1"]["textures"]["level_one_bossRight"]["t"].as_string();
	m_lvlOneBossTxtFileM = mGameData["level_1"]["textures"]["level_one_bossMiddle"]["t"].as_string();
	m_lvlOneBossTxtFileL = mGameData["level_1"]["textures"]["level_one_bossLeft"]["t"].as_string();

	m_LvlOneBossRightArmTxt->loadFromFile(m_lvlOneBossTxtFileR,
		sf::IntRect(int(mGameData["level_1"]["textures"]["level_one_bossRight"]["x"].as<int>()),
			int(mGameData["level_1"]["textures"]["level_one_bossRight"]["y"].as<int>()),
			int(mGameData["level_1"]["textures"]["level_one_bossRight"]["w"].as<int>()),
			int(mGameData["level_1"]["textures"]["level_one_bossRight"]["h"].as<int>())));

	m_LvlOneBossBodyTxt->loadFromFile(m_lvlOneBossTxtFileM,
		sf::IntRect(int(mGameData["level_1"]["textures"]["level_one_bossMiddle"]["x"].as<int>()),
			int(mGameData["level_1"]["textures"]["level_one_bossMiddle"]["y"].as<int>()),
			int(mGameData["level_1"]["textures"]["level_one_bossMiddle"]["w"].as<int>()),
			int(mGameData["level_1"]["textures"]["level_one_bossMiddle"]["h"].as<int>())));

	m_LvlOneBossLeftArmTxt->loadFromFile(m_lvlOneBossTxtFileL,
		sf::IntRect(int(mGameData["level_1"]["textures"]["level_one_bossLeft"]["x"].as<int>()),
			int(mGameData["level_1"]["textures"]["level_one_bossLeft"]["y"].as<int>()),
			int(mGameData["level_1"]["textures"]["level_one_bossLeft"]["w"].as<int>()),
			int(mGameData["level_1"]["textures"]["level_one_bossLeft"]["h"].as<int>())));



	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////MENU
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Button1File = mGameData["level_1"]["textures"]["button1_texture"]["t"].as_string();
	m_Button2File = mGameData["level_1"]["textures"]["button2_texture"]["t"].as_string();
	m_MenuBackgroundFile = mGameData["level_1"]["textures"]["menu_Background"]["t"].as_string();


	////////////////////////////////////TEXTURES///////////////////////////////////////////////	
	m_Button1Texture->loadFromFile(m_Button1File,
		sf::IntRect(int(mGameData["level_1"]["textures"]["button1_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["textures"]["button1_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["textures"]["button1_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["button1_texture"]["h"].as<int>())));

	m_Button2Texture->loadFromFile(m_Button2File,
		sf::IntRect(int(mGameData["level_1"]["textures"]["button2_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["textures"]["button2_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["textures"]["button2_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["button2_texture"]["h"].as<int>())));


	m_MenuBackgroundTexture->loadFromFile(m_MenuBackgroundFile,
		sf::IntRect(int(mGameData["level_1"]["textures"]["menu_Background"]["x"].as<int>()),
		int(mGameData["level_1"]["textures"]["menu_Background"]["y"].as<int>()),
		int(mGameData["level_1"]["textures"]["menu_Background"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["menu_Background"]["h"].as<int>())));


	m_BulletDimensions = new sf::Vector2f(int(mGameData["level_1"]["textures"]["enemy_bullet"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["enemy_bullet"]["h"].as<int>()));

	m_EnemyDimensions = new sf::Vector2f(int(mGameData["level_1"]["textures"]["enemy_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["enemy_texture"]["h"].as<int>()));

	m_PlayerDimensions = new sf::Vector2f(int(mGameData["level_1"]["textures"]["player_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["textures"]["player_texture"]["h"].as<int>()));

}