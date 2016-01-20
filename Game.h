#ifndef __GAME_H__
#define ___GAME_H__


#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Shop.h"
#include "Collision.h"
#include "Training.h"
#include <vector>
#include <SFML/System/Clock.hpp>

class Game
{
	public:
		Game::Game();
		Game::~Game();
		void Game::Init();

		void Game::Run(sf::RenderWindow &w);
		sf::Clock* clock;

	private:
		sf::Texture* back;
		Menu* theMenu;
		Player* thePlayer;
		Bullet* theBullets;
		Enemy* theEnemies;
		Shop* theShop;
		Training* trainingRoom;
		Collision* theCollisions;
		int gameState;
		enum GameState { MENU_RUNNING = 0, SHOP_RUNNING = 1, GAME_RUNNING = 2, TRAINING_MODE = 3, END = 4, };
};

#endif 