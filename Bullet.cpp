#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(float x, float y, bool alive)
{
	bulletTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(134, 283, 3, 9));	// Set bullet texture
	bulletSprite.setTexture(bulletTexture);
	bulletSource = sf::Vector2f(x, y);		// Set initial position of the bullet source
	timeAtLastFire = std::clock();
	fireRate = 50;	// Set fire rate here
	MAX_BULLETS = 200;		// Set max number of bullets here
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bulletFiredA[i] = alive;	// Set all bullets to not alive
	}
}

void Bullet::Update(sf::RenderWindow &w, POINT p)
{
	float dx = (p.x - w.getPosition().x) - bulletSource.x - 8.5f;
	float dy = (p.y - w.getPosition().y) - bulletSource.y - 34;
	float dlength = sqrt((dx*dx) + (dy*dy));
	if (dlength == 0)
		dlength = 0.0000001f;	// Fail-safe to prevent divide by 0 on the next 2 lines
	bulletSourceVelocity.x = (dx / dlength) / 5 * 5;
	bulletSourceVelocity.y = (dy / dlength) / 5 * 5;
	bulletSource += bulletSourceVelocity;	// Get vector between current location and cursor, normalize, and add
	timeNow = std::clock();
	if (bulletSource.x < 18)
		bulletSource.x = 18;
	if (bulletSource.y < 5)
		bulletSource.y = 5;
	if (bulletSource.x > w.getSize().x - 21)
		bulletSource.x = w.getSize().x - 21.0f;
	if (bulletSource.y > w.getSize().y - 30)
		bulletSource.y = w.getSize().y - 30.0f;	// Prevents bullet source following cursor out the window

	FireBullet(bulletSource);	// Fire the bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bulletFiredA[i] == true)
		{
			bulletPosA[i] += bulletVelocityA[i];	// Update position of living bullets
			if (bulletPosA[i].y < -20)
				bulletFiredA[i] = false;	// If the bullets go off the top of the screen, they die
		}
	}
}

void Bullet::Draw(sf::RenderWindow &w)
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bulletFiredA[i] == true)
		{
			bulletSprite.setPosition(bulletPosA[i]);	// Draw a bullet at each location in the array, if they're alive
			w.draw(bulletSprite);
		}
	}
}

bool Bullet::FireBullet(sf::Vector2f bulletS)
{
	if (GetAsyncKeyState(VK_LBUTTON) < 0 && timeNow - timeAtLastFire >= fireRate)	// If left-click is pressed
	{
		timeAtLastFire = std::clock();
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bulletFiredA[i] == false)
			{
				bulletFiredA[i] = true; bulletFiredA[i + 1] = true;	// Shoot a pair of bullets
				bulletPosA[i].x = bulletSource.x + 4; bulletPosA[i].y = bulletSource.y;		// Set bullet sources next to each other
				bulletPosA[i + 1].x = bulletSource.x - 4; bulletPosA[i + 1].y = bulletSource.y;
				bulletVelocityA[i] = sf::Vector2f(0, -7.5f); bulletVelocityA[i + 1] = sf::Vector2f(0, -7.5f);	// Bullets fire in a straight line
				return true;
			}
		}	
	}
	else if (GetAsyncKeyState(VK_RBUTTON) < 0 && timeNow - timeAtLastFire >= fireRate)	// If right-click is pressed
	{
		timeAtLastFire = std::clock();
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (bulletFiredA[i] == false)
			{
				bulletFiredA[i] = true; bulletFiredA[i + 1] = true;
				bulletPosA[i] = bulletSource; bulletPosA[i + 1] = bulletSource; // Bullets share same source
				bulletVelocityA[i] = sf::Vector2f(1.5f, -7.5f); bulletVelocityA[i + 1] = sf::Vector2f(-1.5f, -7.5f); // Bullets fly off forward, at opposite angles, creates "V" shape
				return true;
			}
		}
	}
	return false;
}