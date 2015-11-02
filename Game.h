#ifndef __GAME_H__
#define ___GAME_H__


#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Menu.h"
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
		Menu* theMenu;
		int gameState;
		enum GameState { MENU_RUNNING = 0, GAME_RUNNING = 1, END = 2 };
};

#endif 