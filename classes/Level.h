#ifndef __LEVEL_H__
#define ___LEVEL_H__


#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <vector>
#include <SFML/System/Clock.hpp>
#include "Ship.h"

class Level
{
public:
	Level::Level();
	Level::~Level();
	void Level::Init();

	void Level::Run(sf::RenderWindow &w);

	sf::Clock* clock;

private:
	Enemy* the_Enemy;
	Ship* the_Ship;
};

#endif 