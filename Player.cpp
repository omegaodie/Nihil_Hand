#include "Player.h"

Player::Player(float spawnX, float spawnY, const GameData &gdata) : 
gd(gdata)
{
	shipSprite = new sf::Sprite();
	shipTexture = gd.m_PlayerTexture;
	shipSprite->setTexture(*shipTexture);
	shipSprite->setOrigin(26, 35);
	shipPos = sf::Vector2f(spawnX, spawnY);
	shipSpeed = 5.0f;
}

void Player::Update(sf::RenderWindow &w, POINT p)
{
	dx = (p.x - w.getPosition().x) - shipPos.x;
	dy = (p.y - w.getPosition().y) - shipPos.y;
	float fx = (p.x - w.getPosition().x);
	float fy = (p.y - w.getPosition().y);
	dlength = sqrt((dx*dx) + (dy*dy));
	if (dlength == 0)
		dlength = 0.00000001f;		// Fail-safe to prevent divide by 0 on the next 2 lines
	shipVelocity.x = (dx / dlength) * shipSpeed;
	shipVelocity.y = (dy / dlength) * shipSpeed;
	if (sqrt(((shipPos.x - fx)*(shipPos.x - fx)) + ((shipPos.y - fy)*(shipPos.y - fy))) <= 4)	// Prevents the ship vibrating around
	{																							// the cursor when close to it
		shipPos = sf::Vector2f(p.x - w.getPosition().x, p.y - w.getPosition().y);
	}
	else shipPos += shipVelocity;	// Get vector between current location and cursor, normalize, and add
	if (shipPos.x < 26)
		shipPos.x = 26;
	if (shipPos.y < 35)
		shipPos.y = 35;
	if (shipPos.x > w.getSize().x - 13)
		shipPos.x = w.getSize().x - 13;
	if (shipPos.y > w.getSize().y)
		shipPos.y = w.getSize().y;		// Prevents ship following cursor out the window
}

void Player::Draw(sf::RenderWindow &w)
{
	shipSprite->setPosition(shipPos);
	w.draw(*shipSprite);
}