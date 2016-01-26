#ifndef __LEVEL_H__
#define ___LEVEL_H__



#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "GameData.h"
#include "Collision.h"


class Level
{
public:
	Level::Level(const GameData &gd);
	Level::~Level();

	void Level::initLevel();
	void Level::Run(sf::RenderWindow &w, POINT p);

	void Level::draw(sf::RenderWindow &w);

	void Level::drawBackGround(sf::RenderWindow &w);

	bool Level::getOver();
	void Level::Reset();
private:
	void Level::collisionDetection();
	const GameData & gd;

	sf::Texture* back;
	Player* thePlayer;
	Bullet* theBullets;
	Enemy* theEnemies;
	Shop* theShop;
	Training* trainingRoom;
	sf::Clock theClock;
	sf::Texture* l_BackGround;
	sf::Sprite* l_BckSprite;
	Collision * cM;
	int theLevel; //maybe change to ENUM later
	bool struck;

};

#endif