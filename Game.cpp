#include"Game.h"

Game::Game(){
	the_Enemy = new Enemy(10, 25);
	isRunning = true;
	clock = new sf::Clock();
	the_Enemy->Init(*clock);
	
}

void Game::Run(sf::RenderWindow &w){
	the_Enemy->Update(*clock);//this is how we do it
	the_Enemy->Draw(w);
}

bool* Game::getIsRunning(){
	bool* returnValue = &isRunning;
	return returnValue;
}