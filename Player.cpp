#include "Player.h"

Player::Player()
{

}

Player::Player(float spawnX, float spawnY)
{
	shipTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(42, 3, 39, 36));
	shipSprite.setTexture(shipTexture);
	shipSprite.setOrigin(26, 35);
	shipPos = sf::Vector2f(spawnX, spawnY);
	shipSpeed = 5.0f;
}

void Player::Update(sf::RenderWindow &w, POINT p)
{
	float dx = (p.x - w.getPosition().x) - shipPos.x;
	float dy = (p.y - w.getPosition().y) - shipPos.y;
	float dlength = sqrt((dx*dx) + (dy*dy));
	if (dlength == 0)
		dlength = 0.00000001f;		// Fail-safe to prevent divide by 0 on the next 2 lines
	shipVelocity.x = (dx / dlength) / 5 * shipSpeed;
	shipVelocity.y = (dy / dlength) / 5 * shipSpeed;
	shipPos += shipVelocity;	// Get vector between current location and cursor, normalize, and add
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
	shipSprite.setPosition(shipPos);
	w.draw(shipSprite);
}