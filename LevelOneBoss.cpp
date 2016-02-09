#include "LevelOneBoss.h"

LevelOneBoss::LevelOneBoss(const GameData &gd) : Boss(gd)
{
	bAlive = false;
}

void LevelOneBoss::Init(){
	for (int i = 0; i < 30; i++) {
		rokets[i] = new Rocket(gd);
	}
	leftArm = gd.m_LvlOneBossLeftArmTxt;
	rightArm = gd.m_LvlOneBossRightArmTxt;
	body = gd.m_LvlOneBossBodyTxt;
	lArm = new sf::Sprite();
	rArm = new sf::Sprite();
	bDy = new sf::Sprite();

	for (int i = 0; i < 81; i++) {
		rExplosionTextures[i] = gd.m_RocketAnimTextures[i];
	}



	lA = true;
	rA = true;

	lHp = 1000;
	rHp = 1000;
	bHp = 1000;
	mDirectionX = 1;
	mDirectionY = 1;

	time = sf::Clock();

	timelastfired = time.getElapsedTime().asMilliseconds();

	bVelocity;
	bPosition = new sf::Vector2f(300, 50);
	tesster = 51;
	lArm->setTexture(*leftArm);
	rArm->setTexture(*rightArm);
	bDy->setTexture(*body);
	timeNow = 0;
	bVelocity = new sf::Vector2f(0.2f, 0.2f);
	bAlive = true;

	for (int i = 0; i < 5; i++) {
		explosionColours[i] =
			new sf::Color(lArm->getColor().r - (10 * i), lArm->getColor().b - (20 * i), lArm->getColor().g - (10 * i), 255);
	}
}

void LevelOneBoss::setSpritepositions() {
	lArm->setPosition(*(new sf::Vector2f(bPosition->x, bPosition->y)));
	bDy->setPosition(*(new sf::Vector2f(bPosition->x + 55, bPosition->y - 25)));
	rArm->setPosition(*(new sf::Vector2f(bPosition->x + 172, bPosition->y)));
}

void LevelOneBoss::update(sf::RenderWindow &w) {
	ArtificialIntelligence();
	SectionControl();
	Draw(w);
	for (int i = 0; i < 30; i++) {
		if (rokets[i]->getAlive()) {
			rokets[i]->update();
			rokets[i]->Draw(w);
		}
	}
}

bool LevelOneBoss::getAlive() {
	return bAlive;
}

void LevelOneBoss::Draw(sf::RenderWindow &w){
	setSpritepositions();
	tesster++;
	if (lA == true) {
		w.draw(*lArm);
	}
	if (bAlive) {
		w.draw(*bDy);

	}
	if (rA) {
		w.draw(*rArm);

	}
}

void LevelOneBoss::ArtificialIntelligence(){
	if (bPosition->x < 5) {
		//move right
		mDirectionX = 1;
	}
	if (bPosition->x > 920) {
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
	for (int i = 0; i < 30; i++) {
		if (rokets[i]->getAlive()) {
			currentRockets++;
		}
	}
	if ((currentRockets < 25) && (timelastfired + 750 < time.getElapsedTime().asMilliseconds())) {
		//fireRocket if time elapsed is greater than 1.5 secs
		FireRockets();
		timelastfired = time.getElapsedTime().asMilliseconds();
	}

}

void LevelOneBoss::ImageStuff() {
	//if hit wit bullet
	//lArm->setColor(sf::Color(0, 0, 0, 255));
}


void LevelOneBoss::SectionControl() {
	if (lHp <= 0) {
		lA = false;
	}
	if (rHp <= 0) {
		rA = false;
	}
	if (rHp <= 0) {
		bAlive = false;
	}
}


Rocket* LevelOneBoss::getRockets(int i){
	return rokets[i];
}


void LevelOneBoss::FireRockets() {
	for (int i = 0; i < 10; i++) {
		if (rokets[i]->getAlive() == false) {
			int a = rand() % 40;
			if (a < 10) {
				a = 0;
			}
			else {
				a = 1;
			}
			//rokets[i]->Init(sf::Vector2f(bPosition->x + 125, bPosition->y + 50), a);
			rokets[i]->Init(sf::Vector2f(bPosition->x + 125, bPosition->y + 50), a);
			break;
		}
	}
}


void LevelOneBoss::partDestroyedAnimate(sf::RenderWindow &w) {
	/*for (int k = 0; k < 9; k++) {
	lArm->setPosition(*(new sf::Vector2f(bPosition->x + (k + 10), bPosition->y + ((k / 2) + 10))));
	for (int i = 0; i < 81; i++) {
	lArm->setTexture(*rExplosionTextures[i]);
	w.draw(*lArm);
	}
	}*/
}

sf::Vector2f* LevelOneBoss::getPosition(){
	return bPosition;
}


void LevelOneBoss::isHit(int part){
	if (part == 1){
		//left arm
		lHp -= 50;
	}
	if (part == 2){
		//right arm
		rHp -= 50;
	}
	if (part == 3){//body
		if (lA == false && rA == false){
			bHealth -= 5;
		}
	}
}