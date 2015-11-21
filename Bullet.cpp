#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(float x, float y, bool alive)
{
	enemy = new Enemy();
	player = new Player();
	playerBulletTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(134, 283, 3, 9));	// Set player bullet texture
	enemyBulletTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(210, 284, 8, 8));	// Set enemy bullet texture
	playerBulletSprite.setTexture(playerBulletTexture);
	enemyBulletSprite.setTexture(enemyBulletTexture);
	playerBulletSource = sf::Vector2f(x, y);		// Set initial position of the bullet source
	timeAtLastFire = std::clock();
	fireRate = 50;	// Set fire rate here
	MAX_PLAYER_BULLETS = 100;		// Set max number of bullets here
	for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
	{
		bulletFiredA[i] = alive;	// Set all bullets to not alive
	}
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
	playerbulletSourceVel.x = (dx / dlength) * 5;
	playerbulletSourceVel.y = (dy / dlength) * 5;
	if (sqrt(((playerBulletSource.x - px)*(playerBulletSource.x - px))
		+ ((playerBulletSource.y - py)*(playerBulletSource.y - py))) <= 4)	// Prevents the bullet source vibrating around
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
	HitDetection();
}

void Bullet::HitDetection()
{
	EnemyHitDetection();
	PlayerHitDectection();
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
}

bool Bullet::FireBullet(sf::Vector2f bulletS)
{
	if (GetAsyncKeyState(VK_LBUTTON) < 0 && timeNow - timeAtLastFire >= fireRate)	// If left-click is pressed
	{
		timeAtLastFire = std::clock();
		for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
		{
			if (bulletFiredA[i] == false)
			{
				bulletFiredA[i] = true; bulletFiredA[i + 1] = true;	// Shoot a pair of bullets
				playerBulletPosA[i].x = playerBulletSource.x + 4; playerBulletPosA[i].y = playerBulletSource.y;		// Set bullet sources next to each other
				playerBulletPosA[i + 1].x = playerBulletSource.x - 4; playerBulletPosA[i + 1].y = playerBulletSource.y;
				playerBulletVelocityA[i] = sf::Vector2f(0, -7.5f); playerBulletVelocityA[i + 1] = sf::Vector2f(0, -7.5f);	// Bullets fire in a straight line
				return true;
			}
		}	
	}
	else if (GetAsyncKeyState(VK_RBUTTON) < 0 && timeNow - timeAtLastFire >= fireRate)	// If right-click is pressed
	{
		timeAtLastFire = std::clock();
		for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
		{
			if (bulletFiredA[i] == false)
			{
				bulletFiredA[i] = true; bulletFiredA[i + 1] = true;
				playerBulletPosA[i].x = playerBulletSource.x + 4; playerBulletPosA[i].y = playerBulletSource.y;		// Set bullet sources next to each other
				playerBulletPosA[i + 1].x = playerBulletSource.x - 4; playerBulletPosA[i + 1].y = playerBulletSource.y;
				playerBulletVelocityA[i] = sf::Vector2f(1.5f, -7.5f); playerBulletVelocityA[i + 1] = sf::Vector2f(-1.5f, -7.5f); // Bullets fly off forward, at opposite angles, creates "V" shape
				return true;
			}
		}
	}
	return false;
}

void Bullet::EnemyHitDetection()
{
	for (int b = 0; b < MAX_PLAYER_BULLETS; b++)	// Cycles through all bullets
	{
		if (bulletFiredA[b] == true)	// Checks if they're even alive first
		{
			for (int i = 0; i < 10; i++)	// Checks against all enemies
			{
				if (enemy->enemyAlive[i] == true	// Checks if the enemy's alive, then if the bullets within the enemy
					&& playerBulletPosA[b].x + 3 > enemy->enemyPosition[i].x && playerBulletPosA[b].x < enemy->enemyPosition[i].x + 28
					&& playerBulletPosA[b].y + 9 > enemy->enemyPosition[i].y && playerBulletPosA[b].y < enemy->enemyPosition[i].y + 26)*/
				{
					enemy->enemyAlive[i] = false;	
					bulletFiredA[b] = false;		// Kills the enemy and the bullet
				}
			}
		}
	}
}

void Bullet::PlayerHitDectection()
{
	for (int b = 0; b < MAX_ENEMY_BULLETS; b++)	// Cycles through all bullets
	{
		if (bulletFiredA[b] == false)	// Checks if they're even alive first
		{
			if (enemyBulletPosA[b].x + 8 > player->shipPos.x && enemyBulletPosA[b].x < player->shipPos.x + 39
				&& enemyBulletPosA[b].y + 8 > player->shipPos.y && enemyBulletPosA[b].y < player->shipPos.y + 36)
			{
				// Damage the player
			}
		}
	}
}