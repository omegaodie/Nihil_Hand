#ifndef __GAME_H__
#define ___GAME_H__


#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Game
{
	public:
		Game::Game();
		Game::~Game();
		void Game::Init();

		void Game::Run(sf::RenderWindow &w);

		bool* getIsRunning();

	private:
		bool isRunning;
		Enemy* the_Enemy;

};

#endif 