#include "Level.h"

Level::Level(const GameData &gdata) :
gd(gdata){
	theLevel = 1;
	theClock = sf::Clock();
	cM = new CollisionManager();
	struck = false;
	enemyNum = 9;
}

void Level::initLevel(){
	for (int i = 0; i < enemyNum; i++){
		theEnemies[i] = new Enemy(gd, i);
	}
	
	thePlayer = new Player(120,120,gd);
}
void Level::Run(sf::RenderWindow &w, POINT p){
	for (int i = 0; i < enemyNum; i++){
		theEnemies[i]->Update(theClock);
		theEnemies[i]->FireBullets();
	}
	thePlayer->Update(w, p);
	draw(w);
}

void Level::draw(sf::RenderWindow &w){
	for (int i = 0; i < enemyNum; i++){
		theEnemies[i]->Draw(w);
	}
	
	thePlayer->Draw(w);
	drawBackGround(w);
}

void Level::drawBackGround(sf::RenderWindow &w){

}

void Level::collisionDetection(){
}