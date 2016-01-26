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

	void LevelOneBoss::ArtificialIntelligence();

private:
	sf::Texture *leftArm;
	sf::Texture *rightArm;
	sf::Texture *body;
	sf::Clock time;

	float timelastfired;

	std::vector<Rocket*> rokets;

	int mDirectionX, mDirectionY;

	sf::Sprite *lArm;
	sf::Sprite *rArm;
	sf::Sprite *bDy;

	float lHp, rHp, bHp;
	bool lA, rA;
	
};

#endif 