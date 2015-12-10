#ifndef __LEVEL_H__
#define ___LEVEL_H__



#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "GameData.h"
#include "CollisionManager.h"


class Level
{
public:
	Level::Level(const GameData &gd);
	Level::~Level();

	void Level::initLevel();
	void Level::Run(sf::RenderWindow &w, POINT p);

	void Level::draw(sf::RenderWindow &w);

	void Level::drawBackGround(sf::RenderWindow &w);


private:
	void Level::collisionDetection();
	Enemy* theEnemies[9];
	const GameData & gd;
	int enemyNum;
	Player* thePlayer;
	sf::Clock theClock;
	sf::Texture* l_BackGround;
	CollisionManager * cM;
	int theLevel; //maybe change to ENUM later
	bool struck;

};

#endif