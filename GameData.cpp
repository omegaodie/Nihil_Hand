#include "GameData.h"

GameData::GameData()
{
	if (loaded == false)
	loadGameData();
}

void GameData::loadGameData()
{
	m_EnemyTexture = new sf::Texture();
	m_PlayerTexture = new sf::Texture();
	m_Button1Texture = new sf::Texture();
	m_Button2Texture = new sf::Texture();
	m_MenuBackgroundTexture = new sf::Texture();
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

	//player stuff
	m_PlayerTexture->loadFromFile(m_shipTextureFile,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["player_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["player_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["player_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["player_texture"]["h"].as<int>())));

	///enemy stuff 
	m_EnemyTexture->loadFromFile(m_shipTextureFile,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["enemy_texture"]["x"].as<int>()), 
		int(mGameData["level_1"]["wave_1"]["textures"]["enemy_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["enemy_texture"]["w"].as<int>()), 
		int(mGameData["level_1"]["wave_1"]["textures"]["enemy_texture"]["h"].as<int>())));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////MENU
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_Button1File = mGameData["level_1"]["wave_1"]["textures"]["Button1_texture"]["t"].as_string();
	m_Button2File = mGameData["level_1"]["wave_1"]["textures"]["Button2_texture"]["t"].as_string();
	m_MenuBackgroundFile = mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["t"].as_string();




	////////////////////////////////////TEXTURES///////////////////////////////////////////////	
	m_Button1Texture->loadFromFile(m_Button1File,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["Button1_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["Button1_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["Button1_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["Button1_texture"]["h"].as<int>())));

	m_Button2Texture->loadFromFile(m_Button2File,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["Button2_texture"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["Button2_texture"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["Button2_texture"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["Button2_texture"]["h"].as<int>())));


	m_MenuBackgroundTexture->loadFromFile(m_MenuBackgroundFile,
		sf::IntRect(int(mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["x"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["y"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["w"].as<int>()),
		int(mGameData["level_1"]["wave_1"]["textures"]["menu_Background"]["h"].as<int>())));


	loaded = true;

}