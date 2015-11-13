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

class Bullet
{
public:
	Bullet::Bullet();
	Bullet::Bullet(float x, float y, bool);
	Bullet::~Bullet();

	sf::Texture playerBulletTexture;		// The bullet's texture
	sf::Texture enemyBulletTexture;
	sf::Sprite playerBulletSprite;		// The bullet's sprite
	sf::Sprite enemyBulletSprite;

	sf::Vector2f bulletPosA[200];	// Array of bullet positions
	sf::Vector2f bulletSource;		// Position of where the bullets get shot from
	sf::Vector2f bulletSourceVelocity;		// Velocity for moves around the bullet source
	sf::Vector2f bulletVelocityA[200];		// Array of bullet velocity
	bool bulletFiredA[200];

	float fireRate;		// Rate that bullets can be shot
	std::clock_t timeAtLastFire;	// Time the last bullet was shot
	std::clock_t timeNow;			// Current time
	int MAX_BULLETS;	// Max number of bullets

	void Update(sf::RenderWindow &w, POINT p);		// Update bullet positions, bullet source position, check if off-screen
	void Draw(sf::RenderWindow &w);					// Draw bullets
	bool FireBullet(sf::Vector2f bulletSource);		// Fire the bullets
	float dx, dy, px, py, dlength;
};