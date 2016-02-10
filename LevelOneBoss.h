#pragma once
#ifndef __LEVELONEBOSS_H__
#define ___LEVELONEBOSS_H__

#include "Boss.h"
#include <cmath>


class LevelOneBoss : Boss
{
public:

	LevelOneBoss::LevelOneBoss(const GameData &gd);

	void LevelOneBoss::Init();

	void LevelOneBoss::setSpritepositions();

	void update(sf::RenderWindow & w);

	bool getAlive();


	void LevelOneBoss::Draw(sf::RenderWindow &w);

	void LevelOneBoss::ImageStuff();

	void LevelOneBoss::SectionControl();

	void LevelOneBoss::FireRockets();

	void LevelOneBoss::partDestroyedAnimate(sf::RenderWindow &w);

	void LevelOneBoss::ArtificialIntelligence();

	sf::Vector2f* LevelOneBoss::getPosition();

	void LevelOneBoss::isHit(int);

	Rocket* LevelOneBoss::getRockets(int i);

	void LevelOneBoss::SpeedUp();

	bool lA, rA;

private:
	sf::Texture *leftArm;
	sf::Texture *rightArm;
	sf::Texture *body;
	sf::Color* explosionColours[5];
	sf::Clock time;

	sf::Texture* rExplosionTextures[81];

	int speed;

	int fireRate;
	float slowDownTimer;

	float timelastfired;

	Rocket* rokets[100];

	int mDirectionX, mDirectionY;

	sf::Sprite *lArm;
	sf::Sprite *rArm;
	sf::Sprite *bDy;

	float lHp, rHp, bHp;
	

};

#endif 