#include "Level.h"
int thingy = 0;

Level::Level(const GameData &gdata) :
gd(gdata){
	//struck = false;
	//theLevel = 1;
	//theClock = sf::Clock();
	//cM = new Collision();
	//struck = false;

	//l_BackGround = gd.m_lvl1BackGroundTexture;
	//l_BckSprite = new sf::Sprite(*l_BackGround);
	//l_BckSprite->setPosition(20, -1000);
}

void Level::initLevel(){
	//theEnemies[i] = new Enemy();
	//thePlayer = new Player(120,120,gd);
}

bool Level::getOver() {
	return struck;
}


void Level::Run(sf::RenderWindow &w, POINT p){

	//if (thePlayer->playerHealth > 0)
	//{
	//	theBullets->Update(w, p);
	//	theEnemies->Update(2);
	//	theEnemies->Draw(w, 2);
	//	cM->CheckForCollision(w);
	//	thePlayer->Update(w, p);
	//	thePlayer->Draw(w, 0);				 // Level state
	//}
	//if (thePlayer->playerHealth <= 0) { thePlayer->DrawGameOver(w); }
	//thingy++;
	//collisionDetection();
	//for (int i = 0; i < enemyNum; i++){
	//	theEnemies[i]->Update(theClock);
	//	if (thingy > 100) {
	//		theEnemies[i]->FireBullets();
	//		if (i >= enemyNum - 1){
	//			thingy = 0;
	//		}
	//	}	
	//}
	//thePlayer->Update(w, p);
	//draw(w);
}

void Level::draw(sf::RenderWindow &w){
	/*drawBackGround(w);
	for (int i = 0; i < enemyNum; i++){
		if (theEnemies[i]->isAlive()) {
			theEnemies[i]->Draw(w);
		}
	}
	thePlayer->Draw(w);*/
	
}

void Level::drawBackGround(sf::RenderWindow &w){
	/*int p = l_BckSprite->getPosition().y + w.getSize().y;
	int q = l_BackGround->getSize().y;
	if (l_BckSprite->getPosition().y + (w.getSize().y + w.getSize().y) > l_BackGround->getSize().y - (w.getSize().y + w.getSize().y)) {
		l_BckSprite->setPosition((sf::Vector2f(l_BckSprite->getPosition().x, -1200)));
	}
	else {
		l_BckSprite->setPosition((sf::Vector2f(l_BckSprite->getPosition().x, l_BckSprite->getPosition().y + 2)));
		
	}
	w.draw(*l_BckSprite);*/
}

void Level::Reset() {
	/*struck = false;
	theLevel = 1;
	theClock = sf::Clock();
	cM = new CollisionManager();
	struck = false;
	enemyNum = 9;
	l_BackGround = gd.m_lvl1BackGroundTexture;
	l_BckSprite = new sf::Sprite(*l_BackGround);
	l_BckSprite->setPosition(20, -1000);
	initLevel();*/
}

void Level::collisionDetection(){

	/*for (int i = 0; i < enemyNum; i++) {
		if (theEnemies[i]->isAlive()) {
			if (cM->HitDetectionEnemyPlayer(thePlayer->GetPos(), theEnemies[i]->GetPos(),
				new sf::Vector2f(gd.m_PlayerTexture->getSize()), new sf::Vector2f(gd.m_EnemyTexture->getSize()))) {
				if (thePlayer->tookaHit()) {
					struck = true;
				}
			}
		}
	}
	for (int i = 0; i < enemyNum; i++) {
		if (theEnemies[i]->isAlive()) {
			cM->HitDetectionPlayerBulletEnemy(thePlayer->getBullets(), theEnemies[i]);
		}
	}*/
}