#pragma once
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Training.h"
#include "Boss.h"

class Collision
{
private:
	Bullet* myBullets;
	Enemy* myEnemies;
	Boss* theBoss;
	Player* myPlayer;
	Training* myTest;
	float playerDmg, shieldPower, chargePower;
	bool mercyInvuln, shieldActive, chargeActive;
	int spells, blastPower, mercyPower, myMode;
	sf::Font spellFont;
	sf::Text spellText;
	std::string spellString;

	sf::Texture droneExplosionTexture;
	sf::Texture shieldTexture;
	sf::Texture invulnTexture;
	sf::Sprite droneExplosionSprite;
	sf::Sprite shieldSprite;
	sf::Sprite invulnSprite;
	sf::Vector2f droneExplosionPos[10];
	bool droneExplosionInUse[10];
	sf::Vector2f sentryDirections[8];

	bool Collision::TrainingCollisions();
	bool Collision::EnemyFiring();			// Manage the enemies firing bullets
	void Collision::CleanBullets();			// Clear bullets that have gone off-screen
	
	
public:
	Collision::Collision();
	Collision::Collision(Enemy* enemies, Bullet* bullets, Player* player, Training* test, int mode, float playerDamage, int blastDamage, float chargeStat, float shieldStat, float mercyStat, int maxSpells);
	Collision::~Collision();

	void Collision::CheckForCollision(sf::RenderWindow &w);	// Check for collisions between the player, enemies, and bullets
	void Collision::FireSpell(sf::Event &eve);		// Use a spell
	void Collision::DrawShield(sf::RenderWindow &w);	// Draw the shield
	bool Collision::TestWallCollisions();	// Collision against the training room walls
};