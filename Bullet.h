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
#include <istream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Enemy.h"
#include "Player.h"

class Bullet
{
public:
	Bullet::Bullet();
	Bullet::Bullet(float x, float y, bool, float speed);
	Bullet::~Bullet();
	Enemy* enemy;
	Player* player;
	float shipSpeed;

	sf::Texture playerBulletTexture;		// The player bullet texture
	sf::Texture enemyBulletTexture;			// The enemy bullet texture
	sf::Sprite playerBulletSprite;		// The player bullet sprite
	sf::Sprite enemyBulletSprite;		// The enemy bullet sprite

	sf::Vector2f bSource[2];
	sf::Vector2f bVel[2];
	sf::Vector2f playerBulletPosA[100];	// Array of bullet positions
	sf::Vector2f playerBulletSource;		// Position of where the bullets get shot from
	sf::Vector2f playerbulletSourceVel;		// Velocity for moving around the bullet source
	sf::Vector2f playerBulletVelocityA[100];		// Array of bullet velocity
	sf::Vector2f enemyBulletPosA[200];	// Array of bullet positions
	sf::Vector2f enemyBulletSource[10];		// Position of where the bullets get shot from
	sf::Vector2f enemyBulletVelocityA[200];		// Array of bullet velocity
	bool bulletFiredA[300];
	bool enemyBulletFired[200];

	float fireRate;		// Rate that bullets can be shot
	std::clock_t timeAtLastFire;	// Time the last bullet was shot
	std::clock_t timeAtLastDroneFire;
	std::clock_t timeAtLastSweepFire;
	std::clock_t timeNow;			// Current time
	int MAX_ENEMY_BULLETS;	// Max number of enemy bullets
	int MAX_PLAYER_BULLETS;	// Max number of player bullets

	void Bullet::Update(sf::RenderWindow &w, POINT p);		// Update bullet positions, bullet source position, check if off-screen
	void Bullet::Draw(sf::RenderWindow &w);					// Draw bullets
	bool Bullet::FireBullet(sf::Vector2f bulletSource);		// Fire the bullets
	float dx, dy, px, py, dlength;
private:
	sf::Font spellFont;
	sf::Text spellText;
	std::string spellString;

	sf::Texture HUDSpellTexture;
	sf::Sprite HUDSpellSprite;
};