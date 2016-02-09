#include "Level.h"
int thingy = 0;



Level::Level(const GameData &gdata) :
gd(gdata){
	bckX = 0;
	bckY = 0;
	bossIniated = false;
	bossSpawn = gd.BossSpawnTime;
	//the_Enemy = new Enemy(10, 25);
	clock = new sf::Clock();
	//theMenu = new Menu(gd);
	thePlayer = new Player();
	struck = false;
	boss = new LevelOneBoss(gd);
	//thePlayer = new Player(308.5f, 334);
	//theBullets = new Bullet(300, 300, false);
	theEnemies = new Enemy(gd);
	//theBullets = new Bullet();
	theShop = new Shop();
	//theCollisions = new Collision(theBullets, theEnemies);
	//trainingRoom = new Training(theEnemies);

	back = new sf::Texture();
	back = (gd.m_lvl1BackGroundTexture);
	l_BckSprite = new sf::Sprite();
	l_BckSprite->setTexture(*back);
	l_BckSprite->setPosition(0, 4000);
}

void Level::initLevel(){
	bckX = 0;
	bckY = 0;
	bossIniated = false;
	bossSpawn = gd.BossSpawnTime;
	clock = new sf::Clock();
	thePlayer = new Player();
	struck = false;
	boss = new LevelOneBoss(gd);
	theEnemies = new Enemy(gd);
	theShop = new Shop();
}

bool Level::getOver() {
	return struck;
}

void Level::RocketOnShipCollisions(){
	for (int i = 0; i < 30; i++){
		if (boss->getRockets(i)->getAlive() == true){
			if (thePlayer->shipPos.x > boss->getRockets(i)->getPosition().x - 50 &&
				thePlayer->shipPos.x <  boss->getRockets(i)->getPosition().x + 50 &&
				thePlayer->shipPos.y >  boss->getRockets(i)->getPosition().y - 50 &&
				thePlayer->shipPos.y <  boss->getRockets(i)->getPosition().y + 50){
				boss->getRockets(i)->RandomlyExplode();
				thePlayer->playerHealth -= 50;
			}
		}
	}
}


void Level::GetStats(std::vector<float> playerStats){
	bossIniated = false;
	thePlayer = new Player(308.5f, 334, playerStats.at(3), playerStats.at(4), playerStats.at(8), playerStats.at(9), theShop->playerScore);
	theBullets = new Bullet(300, 300, false, playerStats.at(8), gd);
	theEnemies = new Enemy(2, gd);
	trainingRoom = new Training(theEnemies);
	trainingRoom->musicChannel->setMute(false);
	cM = new Collision(theEnemies, theBullets, thePlayer, trainingRoom, 3, playerStats.at(0),
		playerStats.at(1), playerStats.at(2), playerStats.at(3), playerStats.at(5), playerStats.at(6), 
		playerStats.at(7), playerStats.at(10), playerStats.at(11), gd, boss);
}

void Level::Run(sf::RenderWindow &w, POINT p){
	draw(w);
	//cM->FireSpell(eve);
	if (clock->getElapsedTime().asMilliseconds() > bossSpawn){
		if (bossIniated == false){
			boss->Init();
			bossIniated = true;
		}if (boss->getAlive()) {
			boss->update(w);
			RocketOnShipCollisions();
		}else{
			struck = true;
		}
	}
	
	 if (thePlayer->playerHealth > 0)
	 {
		theBullets->Update(w, p);
		theEnemies->Update(2);
		theEnemies->Draw(w, 2);
		cM->CheckForCollision(w);
		thePlayer->Update(w, p);
		thePlayer->Draw(w, 0);				 // Level state
	 }
	 if (thePlayer->playerHealth <= 0) { 
		 thePlayer->DrawGameOver(w); 
	 }
	 if (thePlayer->state() == 2)
		 {
			 theShop->SetPlayerScore(thePlayer->playerScore);
			 theShop->GameStart = 0;
			 //theShop->musicChannel->setMute(false);
		}
	}

void Level::draw(sf::RenderWindow &w){
	RunBackground(w);
}


void Level::Reset() {
	struck = false;
	theLevel = 1;
	initLevel();
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

void Level::RunBackground(sf::RenderWindow &w){

	if (bckY + w.getSize().y < back->getSize().y){
		bckY -= 2;
	}
	else{
		bckY = 0;
	}
	l_BckSprite->setPosition(sf::Vector2f(bckX, bckY));
	w.draw(*l_BckSprite);
}