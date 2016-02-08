#ifndef __LEVEL_H__
#define ___LEVEL_H__



#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "GameData.h"
#include "Collision.h"
#include "LevelOneBoss.h"
#include "Rocket.h"


class Level
{
public:
	Level::Level(const GameData &gd);
	//Level::~Level();

	void Level::initLevel();
	void Level::Run(sf::RenderWindow &w, POINT p);

	void Level::draw(sf::RenderWindow &w);

	void Level::drawBackGround(sf::RenderWindow &w);

	bool Level::getOver();
	void Level::Reset();

	void Level::RocketOnShipCollisions();

	void Level::RunBackground(sf::RenderWindow &w);

	void Level::GetStats(std::vector<float> playerStats);

private:
	void Level::collisionDetection();
	const GameData & gd;
	sf::Clock* clock;
	sf::Texture* back;
	Player* thePlayer;
	LevelOneBoss* boss;
	Bullet* theBullets;
	Enemy* theEnemies;
	Shop* theShop;
	Training* trainingRoom;
	sf::Clock theClock;
	sf::Texture* l_BackGround;
	sf::Sprite* l_BckSprite;
	Collision * cM;
	int theLevel, bckX, bckY, bossSpawn; //maybe change to ENUM later
	bool struck; 
	bool bossIniated;

};

#endif