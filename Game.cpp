#include"Game.h"

Game::Game(){
	//the_Enemy = new Enemy(10, 25);
	clock = new sf::Clock();
	theMenu = new Menu();
	theMenu->Init();
	//the_Enemy->Init(*clock);
	gameState = MENU_RUNNING;
}
	


void Game::Run(sf::RenderWindow &w){
	sf::Event eve;
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
							 // Level state
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