#include "Collision.h"

Collision::Collision()
{

}

Collision::Collision(Enemy* enemies, Bullet* bullets, Player* player, float playerDamage)
{
	myBullets = bullets;
	myEnemies = enemies;
	myPlayer = player;
	playerDmg = playerDamage;
}

void Collision::CheckForCollision()
{
	for (int b = 0; b < 200; b++)	// Cycles through all bullets / Player bullet on enemy ship collision
	{
		if (myBullets->bulletFiredA[b] == true)	// Checks if they're even alive first
		{
			for (int i = 0; i < 10; i++)	// Checks against all enemies
			{
				if (myEnemies->enemyAlive[i] == true	// Checks if the enemies alive, then if the bullets within the enemy
					&& myBullets->playerBulletPosA[b].x < myEnemies->enemyPosition[i].x && myBullets->playerBulletPosA[b].x + 3 > myEnemies->enemyPosition[i].x - 28
					&& myBullets->playerBulletPosA[b].y < myEnemies->enemyPosition[i].y + 10 && myBullets->playerBulletPosA[b].y + 9 > myEnemies->enemyPosition[i].y)
				{
					myEnemies->enemyHealth[i] -= playerDmg;
					myBullets->bulletFiredA[b] = false;		// Kills the enemy and the bullet
				}
			}
		}
	}
	//std::cout << myPlayer->shipPos.x << std::endl;
	for (int b = 0; b < 200; b++)	// Enemy bullets on player ship collision
	{
		if (myBullets->enemyBulletFired[b] == true)	// Checks if they're even alive first
		{
			if (myPlayer->shipPos.x - 26 < myBullets->enemyBulletPosA[b].x && myPlayer->shipPos.x + 13 > myBullets->enemyBulletPosA[b].x + 8
				&& myPlayer->shipPos.y - 26 < myBullets->enemyBulletPosA[b].y && myPlayer->shipPos.y + 13 > myBullets->enemyBulletPosA[b].y + 8)
			{
				myPlayer->playerHealth -= 5;
				myBullets->enemyBulletFired[b] = false;
			}
		}
	}
	for (int i = 0; i < 10; i++)	// Player ship on enemy ship collision
	{
		if (myEnemies->enemyAlive[i] == true	// Checks if the enemies alive, then if the bullets within the enemy
			&& myPlayer->shipPos.x < myEnemies->enemyPosition[i].x + 28 && myPlayer->shipPos.x + 39 > myEnemies->enemyPosition[i].x
			&& myPlayer->shipPos.y < myEnemies->enemyPosition[i].y + 15 && myPlayer->shipPos.y + 36 > myEnemies->enemyPosition[i].y)
		{
			myPlayer->playerHealth -= 5;
		}
	}
	EnemyFiring();
}

bool Collision::EnemyFiring() {
	if (myBullets->timeNow - myBullets->timeAtLastEnemyFire >= 1000)
	{
		myBullets->timeAtLastEnemyFire = std::clock();
		for (int i = 0; i < 10; i++)
		{
			if (myEnemies->enemyAlive[i] == true)
			{
				for (int b = 0; b < myBullets->MAX_ENEMY_BULLETS; b++)
				{
					if (myBullets->enemyBulletFired[b] == false)
						//if (i <= 10)
					{
						myBullets->enemyBulletFired[b] = true;
						myBullets->enemyBulletPosA[b] = sf::Vector2f(myEnemies->enemyPosition[i].x - 18, myEnemies->enemyPosition[i].y - 5);
						myBullets->enemyBulletVelocityA[b] = sf::Vector2f(0, 2.5f + myEnemies->enemyVelocity[i].y);
						goto skip;
					}
				}
			}
		skip:;
		}
		return true;
	}
}
