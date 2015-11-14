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
	gamedata = json::parse_file("resources/GeneralGameData.json");

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
	/////////////////////////////////////////////////////////////////////////////
	///GAME 
	/////////////////////////////////////////////////////////////////////////////
	//enemy and player sprite sheet
	m_shipTextureFile = mGameData["level_1"]["wave_1"]["textures"]["enemy_texture"]["t"].as_string();

	m_lvl1BackGround = mGameData["level_1"]["wave_1"]["textures"]["lvl_1_texture"]["t"].as_string();

	m_lvl1BackGroundTexture->loadFromFile(m_lvl1BackGround,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["lvl_1_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["lvl_1_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["lvl_1_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["lvl_1_texture"]["h"].as<int>())));




	//player stuff
	m_PlayerTexture->loadFromFile(m_shipTextureFile,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["player_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["player_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["player_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["player_texture"]["h"].as<int>())));

	m_PlayerBulletTexture->loadFromFile(m_shipTextureFile, 
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["player_bullet"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["player_bullet"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["player_bullet"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["player_bullet"]["h"].as<int>())));

	///enemy stuff 
	m_EnemyTexture->loadFromFile(m_shipTextureFile,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["enemy_texture"]["x"].as<int>()), 
		int(mGameData["level_1"]["wave_1"]["textures"]["enemy_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["enemy_texture"]["w"].as<int>()), 
		int(mGameData["level_1"]["wave_1"]["textures"]["enemy_texture"]["h"].as<int>())));

	m_EnemyBulletTexture->loadFromFile(m_shipTextureFile,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["enemy_bullet"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["enemy_bullet"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["enemy_bullet"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["enemy_bullet"]["h"].as<int>())));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////MENU
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Button1File = mGameData["level_1"]["wave_1"]["textures"]["button1_texture"]["t"].as_string();
	m_Button2File = mGameData["level_1"]["wave_1"]["textures"]["button2_texture"]["t"].as_string();
	m_MenuBackgroundFile = mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["t"].as_string();


	////////////////////////////////////TEXTURES///////////////////////////////////////////////	
	m_Button1Texture->loadFromFile(m_Button1File,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["button1_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["button1_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["button1_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["button1_texture"]["h"].as<int>())));

	m_Button2Texture->loadFromFile(m_Button2File,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["button2_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["button2_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["button2_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["button2_texture"]["h"].as<int>())));


	m_MenuBackgroundTexture->loadFromFile(m_MenuBackgroundFile,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["h"].as<int>())));

}