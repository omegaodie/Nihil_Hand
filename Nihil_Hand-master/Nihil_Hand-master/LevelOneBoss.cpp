#include "LevelOneBoss.h"

LevelOneBoss::LevelOneBoss(const GameData &gd) : Boss(gd)
{
	bAlive = false;
	for (int i = 0; i < 10; i++) {
		rokets.push_back(new Rocket(gd));
	}
	rokets.shrink_to_fit();
}

void LevelOneBoss::Init(){
	 leftArm = gd.m_LvlOneBossLeftArmTxt;
	 rightArm = gd.m_LvlOneBossRightArmTxt;
	 body = gd.m_LvlOneBossBodyTxt;
	 lArm = new sf::Sprite();
	 rArm = new sf::Sprite();
	 bDy = new sf::Sprite();
	
	 lA, rA = true;
	 lHp, rHp, bHp = 100;
	 mDirectionX = 1;
	 mDirectionY = 1;

	 time = sf::Clock();

	 timelastfired = time.getElapsedTime().asMilliseconds();

	 bVelocity;
	 bPosition = new sf::Vector2f(300, 50);

	 lArm->setTexture(*leftArm);
	 rArm->setTexture(*rightArm);
	 bDy->setTexture(*body);
	 
	 timeNow = 0;
	 bVelocity = new sf::Vector2f(0.2f, 0.2f);
	 bAlive = true;
}

 void LevelOneBoss::setSpritepositions() {
	 lArm->setPosition(*(new sf::Vector2f(bPosition->x, bPosition->y)));
	 bDy->setPosition(*(new sf::Vector2f(bPosition->x + 55, bPosition->y - 30)));
	 rArm->setPosition(*(new sf::Vector2f(bPosition->x + 155, bPosition->y)));
 }

 void LevelOneBoss::update(sf::RenderWindow &w) {
	 ArtificialIntelligence();
	 Draw(w);
	 for (int i = 0; i < 10; i++) {
		 if (rokets[i]->getAlive()) {
			 rokets[i]->update();
		 }
	 }
 }

 bool LevelOneBoss::getAlive() {
	 return bAlive;
 }

void LevelOneBoss::Draw(sf::RenderWindow &w){
	setSpritepositions();
	if (lA){
		w.draw(*lArm);
	}
	if (bAlive){
		w.draw(*bDy);
	}
	if (rA){
		w.draw(*rArm);
	}
	for (int i = 0; i < 10; i++) {
		if (rokets[i]->getAlive()) {
			rokets[i]->Draw(w);
		}
	}
}

void LevelOneBoss::ArtificialIntelligence(){
	if (bPosition->x < 5) {
		//move right
		mDirectionX = 1;
	}
	if (bPosition->x > 500) {
		//move left
		mDirectionX = -1;
	}
	if (bPosition->y > 120) {
		//move up
		mDirectionY = -1;
	}
	if (bPosition->y < 10) {
		//move down
		mDirectionY = 1;
	}
	int currentRockets = 0;
	bPosition->x += mDirectionX * 2;
	bPosition->y += mDirectionY * 2;
	for (int i = 0; i < 10; i++) {
		if (rokets[i]->getAlive()) {
			currentRockets++;
		} 
	}
	if ((currentRockets < 3)&&(timelastfired + 750 < time.getElapsedTime().asMilliseconds())) {
		//fireRocket if time elapsed is greater than 1.5 secs
		FireRockets();
		timelastfired = time.getElapsedTime().asMilliseconds();
	}
	
}

void LevelOneBoss::ImageStuff() {
	//if hit wit bullet
	lArm->setColor(sf::Color(0, 0, 0, 255));
}


void LevelOneBoss::SectionControl() {
	if (lHp < 0) {
		lA = false;
	}
	if (rHp < 0) {
		rA = false;
	}
	if (rHp < 0) {
		bAlive = false;
	}
}

void LevelOneBoss::FireRockets() {
	for (int i = 0; i < 10; i++) {
		if (rokets[i]->getAlive() == false) {
			int a = time.getElapsedTime().asSeconds() / 2;
			if (a != 0)
				a = 1;
			rokets[i]->Init(new sf::Vector2f(bPosition->x + 125, bPosition->y + 50), a);
			break;
		}
	}
}