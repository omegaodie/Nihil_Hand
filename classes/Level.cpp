#include "Level.h"

Level::Level(){
	the_Enemy = new Enemy(20, 20);
	the_Ship = new Ship(100, 100);
}


void Level::Init(){

}

void Level::Run(sf::RenderWindow &w){
	the_Enemy->Draw(w);
	the_Ship->Draw(w);
}