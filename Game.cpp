#include"Game.h"

Game::Game(){
	the_Enemy = new Enemy(10, 25);
	isRunning = true;
	clock = new sf::Clock();
	theMenu = new Menu();
	theMenu->Init();
	the_Enemy->Init(*clock);
	
}

void Game::Run(sf::RenderWindow &w){
	theMenu->Run(w);
	the_Enemy->Update(*clock);//this is how we do it
	the_Enemy->Draw(w);
	
}

bool* Game::getIsRunning(){
	bool* returnValue = &isRunning;
	return returnValue;
}