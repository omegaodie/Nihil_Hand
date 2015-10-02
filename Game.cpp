#include"Game.h"

Game::Game(){
	the_Enemy = new Enemy(10, 25);
	isRunning = true;
}

void Game::Run(sf::RenderWindow &w){
	the_Enemy->Update();
	the_Enemy->Draw(w);
}

bool* Game::getIsRunning(){
	bool* returnValue = &isRunning;
	return returnValue;
}