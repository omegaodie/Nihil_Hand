#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(float x, float y, bool alive, float speed)
{
	playerBulletTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(134, 283, 3, 9));	// Set player bullet texture
	enemyBulletTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(210, 284, 8, 8));	// Set enemy bullet texture
	HUDSpellTexture.loadFromFile("resources/HUDSpellsTexture.png");
	playerBulletSprite.setTexture(playerBulletTexture);
	enemyBulletSprite.setTexture(enemyBulletTexture);
	HUDSpellSprite.setTexture(HUDSpellTexture); HUDSpellSprite.setPosition(120, 457);
	playerBulletSource = sf::Vector2f(x, y);		// Set initial position of the bullet source
	timeAtLastFire = std::clock();
	timeAtLastDroneFire = std::clock();
	timeAtLastSweepFire = std::clock();
	fireRate = 35;	// Set fire rate here
	MAX_PLAYER_BULLETS = 100;		// Set max number of bullets here
	MAX_ENEMY_BULLETS = 200;
	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
	{
		bulletFiredA[i] = alive;	// Set all bullets to not alive
		enemyBulletFired[i] = alive;
	}
	shipSpeed = 5.0f * speed;
	bVel[0] = sf::Vector2f(-1.5f, -15.0f); 
	bVel[1] = sf::Vector2f(1.5f, -15.0f);
}

void Bullet::Update(sf::RenderWindow &w, POINT p)
{
	dx = (p.x - w.getPosition().x) - playerBulletSource.x - 8.5f;
	dy = (p.y - w.getPosition().y) - playerBulletSource.y - 34;
	px = (p.x - w.getPosition().x) - 8.5f;
	py = (p.y - w.getPosition().y) - 34;
	dlength = sqrt((dx*dx) + (dy*dy));
	if (dlength == 0)
		dlength = 0.0000001f;	// Fail-safe to prevent divide by 0 on the next 2 lines
	playerbulletSourceVel.x = (dx / dlength) * shipSpeed;
	playerbulletSourceVel.y = (dy / dlength) * shipSpeed;
	if (sqrt(((playerBulletSource.x - px)*(playerBulletSource.x - px))
		+ ((playerBulletSource.y - py)*(playerBulletSource.y - py))) <= shipSpeed)	// Prevents the bullet source vibrating around
	{																		// the cursor when close to it
		playerBulletSource = sf::Vector2f(p.x - w.getPosition().x - 8.5f, p.y - w.getPosition().y - 34);
	}
	else playerBulletSource += playerbulletSourceVel;	// Get vector between current location and cursor, normalize, and add
	timeNow = std::clock();
	if (playerBulletSource.x < 18)
		playerBulletSource.x = 18;
	if (playerBulletSource.y < 5)
		playerBulletSource.y = 5;
	if (playerBulletSource.x > w.getSize().x - 21)
		playerBulletSource.x = w.getSize().x - 21.0f;
	if (playerBulletSource.y > w.getSize().y - 30)
		playerBulletSource.y = w.getSize().y - 30.0f;	// Prevents bullet source following cursor out the window

	bSource[0] = sf::Vector2f(playerBulletSource.x - 4, playerBulletSource.y);
	bSource[1] = sf::Vector2f(playerBulletSource.x + 4, playerBulletSource.y);	// Two sources for the bullets to shoot out of

	FireBullet(playerBulletSource);	// Fire the bullets

	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
	{
		if (bulletFiredA[i] == true)
		{
			playerBulletPosA[i] += playerBulletVelocityA[i];	// Update position of living bullets
			if (playerBulletPosA[i].y < -20)
				bulletFiredA[i] = false;	// If the bullets go off the top of the screen, they die
		}
	}
	for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
	{
		if (enemyBulletFired[i] == true)
		{
			enemyBulletPosA[i] += enemyBulletVelocityA[i];	// Update position of living bullets
			if (enemyBulletPosA[i].y > 600)
				enemyBulletFired[i] = false;	// If the bullets go off the top of the screen, they die
		}
	}
	Draw(w);
}

void Bullet::Draw(sf::RenderWindow &w)
{
	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
	{
		if (bulletFiredA[i] == true)
		{
			playerBulletSprite.setPosition(playerBulletPosA[i]);	// Draw a bullet at each location in the array, if they're alive
			w.draw(playerBulletSprite);
		}
	}
	for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
	{
		if (enemyBulletFired[i] == true)
		{
			enemyBulletSprite.setPosition(enemyBulletPosA[i]);	// Draw a bullet at each location in the array, if they're alive
			w.draw(enemyBulletSprite);
		}
	}
	w.draw(spellText);
	w.draw(HUDSpellSprite);
}

bool Bullet::FireBullet(sf::Vector2f bulletS)
{
	if (GetAsyncKeyState(VK_LBUTTON) < 0 && timeNow - timeAtLastFire >= fireRate)	// If left-click is pressed
	{
		timeAtLastFire = std::clock();
		for (int b = 0; b < 2; b++)		// Fires two streams of bullets
		{
			for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
			{
				if (bulletFiredA[i] == false)
				{
					bulletFiredA[i] = true; // Shoot a pair of bullets
					playerBulletPosA[i] = bSource[b];	// Set bullet sources next to each other
					playerBulletVelocityA[i] = sf::Vector2f(0, -15.0f);	// Bullets fire in a straight line
					goto skip;
				}
			}
		skip:;
		}
		return true;
	}
	else if (GetAsyncKeyState(VK_RBUTTON) < 0 && timeNow - timeAtLastFire >= fireRate)	// If right-click is pressed
	{
		timeAtLastFire = std::clock();
		for (int b = 0; b < 2; b++)
		{
			for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
			{
				if (bulletFiredA[i] == false)
				{
					bulletFiredA[i] = true;
					playerBulletPosA[i] = bSource[b];	// Set bullet sources next to each other
					playerBulletVelocityA[i] = bVel[b]; // Bullets fly off forward, at opposite angles, creates "V" shape
					goto skipSplit;
				}
			}
		skipSplit:;
		}
		return true;
	}
	return false;
}