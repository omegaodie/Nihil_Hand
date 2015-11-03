#include"Game.h"

Game::Game(){
	theLevel = new Level();
	clock = new sf::Clock();
	theMenu = new Menu();
	theMenu->Init();
	gameState = MENU_RUNNING;
}
	


void Game::Run(sf::RenderWindow &w){
	sf::Event eve;
	sf::Vector2f p = sf::Vector2f(0, 0);
		switch (gameState){
		case MENU_RUNNING:
		{
			theMenu->Run(w, eve);
			if (theMenu->state() == 1){
				gameState = GAME_RUNNING;
			}
		}
		break;
		case GAME_RUNNING:
		{
			theLevel->Run(w);
		}
		break;
		case END:
		{
			w.close();
			// End state
		}
			break;
		}
	
}