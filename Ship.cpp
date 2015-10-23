#include "stdafx.h"
#include "Ship.h"
#include "Bullet.h"

Ship::Ship()
{

}
Ship::Ship(float x, float y)
{
	shipTexture.loadFromFile("shipSheet.png", sf::IntRect(42, 3, 39, 36));
	shipSprite.setTexture(shipTexture);
	shipSprite.setOrigin(26, 35);
	shipPos = sf::Vector2f(x, y);
	shipSpeed = 1.0f;
}

void Ship::Update(sf::RenderWindow &w)
{
	POINT p;
	GetCursorPos(&p);
	float dx = (p.x - w.getPosition().x) - shipPos.x;
	float dy = (p.y - w.getPosition().y) - shipPos.y;
	float dlength = sqrt((dx*dx) + (dy*dy));
	shipVelocity.x = (dx / dlength) / 25 * shipSpeed;
	shipVelocity.y = (dy / dlength) / 25 * shipSpeed;
	shipPos += shipVelocity;
	if (shipPos.x < 26)
		shipPos.x = 27;
	if (shipPos.y < 35)
		shipPos.y = 36;
	if (shipPos.x > w.getSize().x)
		shipPos.x = w.getSize().x;
	if (shipPos.y > w.getSize().y)
		shipPos.y = w.getSize().y;
	FireBullet();
}

void Ship::FireBullet()
{
	
}

void Ship::Draw(sf::RenderWindow &w)
{
	shipSprite.setPosition(shipPos);
	w.draw(shipSprite);
}

sf::Vector2f Ship::GetShipPos()
{
	return shipPos;
}