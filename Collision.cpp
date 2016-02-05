#include "Collision.h"

Collision::Collision()
{

}

Collision::Collision(Enemy* enemies, Bullet* bullets, Player* player, Training* test, int mode, float playerDamage, int blastDamage, float chargeStat, float shieldStat, float mercyStat, int maxSpells)
{
	myBullets = bullets;
	myEnemies = enemies;
	myPlayer = player;
	myTest = test;
	myMode = mode;
	playerDmg = playerDamage;
	blastPower = blastDamage;
	shieldPower = 1 - shieldStat;
	mercyPower = mercyStat;
	chargePower = chargeStat;
	spells = maxSpells;
	shieldActive = false;
	chargeActive = false;
	mercyInvuln = false;

	droneExplosionTexture.loadFromFile("resources/DroneExplosionSheet.png", sf::IntRect(0, 0, 100, 40));
	droneExplosionSprite.setTexture(droneExplosionTexture);

	shieldTexture.loadFromFile("resources/ShieldTexture.png");
	shieldSprite.setTexture(shieldTexture);

	invulnTexture.loadFromFile("resources/InvincibleTexture.png");
	invulnSprite.setTexture(invulnTexture);

	for (int i = 0; i < 10; i++)
	{
		droneExplosionInUse[i] = false;
	}
	// Directions the sentry fires in. Starts at straight up position and goes clockwise at 45°.
	sentryDirections[0] = sf::Vector2f(0, -3); sentryDirections[1] = sf::Vector2f(sqrt(0.5f) * 3, sqrt(0.5f) * -3);
	sentryDirections[2] = sf::Vector2f(3, 0); sentryDirections[3] = sf::Vector2f(sqrt(0.5f) * 3, sqrt(0.5f) * 3);
	sentryDirections[4] = sf::Vector2f(0, 3); sentryDirections[5] = sf::Vector2f(sqrt(0.5f) * -3, sqrt(0.5f) * 3);
	sentryDirections[6] = sf::Vector2f(-3, 0); sentryDirections[7] = sf::Vector2f(sqrt(0.5f) * -3, sqrt(0.5f) * -3);

	spellFont.loadFromFile("C:\\Windows\\Fonts\\OCRAEXT.TTF");

	spellText.setString("Spells: 0");
	spellText.setFont(spellFont);
	spellText.setCharacterSize(16);
	spellText.setColor(sf::Color::White);
	spellText.setPosition(275, 457);
}

void Collision::CheckForCollision(sf::RenderWindow &w)
{
	//myEnemies->droneCenters.at(d) = sf::Vector2f(440 + (myEnemies->droneDis * d), 100);
	//// Player bullets on enemy ship collision START ////
	bool hit = false;
	for (int b = 0; b < myBullets->MAX_PLAYER_BULLETS; b++)	// Cycles through all bullets
	{
		if (myBullets->bulletFiredA[b] == true)	// Checks if they're even alive first
		{
			for (int i = 0; i < myEnemies->enemiesMade; i++)	// Checks against all enemies
			{
				if (myEnemies->enemyType.at(i) == 0)
				{
					if (myEnemies->enemyAlive[i] == true	// Checks if the enemies alive, then if the bullets within the enemy
						&& myBullets->playerBulletPosA[b].x < myEnemies->enemyPosition.at(i).x && myBullets->playerBulletPosA[b].x + 3 > myEnemies->enemyPosition.at(i).x - 28
						&& myBullets->playerBulletPosA[b].y < myEnemies->enemyPosition.at(i).y && myBullets->playerBulletPosA[b].y + 9 > myEnemies->enemyPosition.at(i).y - 26)
					{
						if (chargeActive)
							myEnemies->enemyHealth.at(i) -= playerDmg * chargePower;
						else
							myEnemies->enemyHealth.at(i) -= playerDmg;
						if (myEnemies->enemyHealth.at(i) <= 0 && hit == false)
						{
							myPlayer->playerScore += 100;
							myEnemies->DroneCentering(i);
							hit = true;
						}
						myBullets->bulletFiredA[b] = false;		// Kills the enemy and the bullet
					}
				}
				if (myEnemies->enemyType.at(i) == 1)
				{
					if (myEnemies->enemyAlive[i] == true	// Checks if the enemies alive, then if the bullets within the enemy
						&& myBullets->playerBulletPosA[b].x < myEnemies->enemyPosition.at(i).x + 32 && myBullets->playerBulletPosA[b].x + 3 > myEnemies->enemyPosition.at(i).x
						&& myBullets->playerBulletPosA[b].y < myEnemies->enemyPosition.at(i).y + 25 && myBullets->playerBulletPosA[b].y + 9 > myEnemies->enemyPosition.at(i).y)
					{
						if (chargeActive)
							myEnemies->enemyHealth.at(i) -= playerDmg * chargePower;
						else
							myEnemies->enemyHealth.at(i) -= playerDmg;
						if (myEnemies->enemyHealth.at(i) <= 0)
							myPlayer->playerScore += 200;
						myBullets->bulletFiredA[b] = false;		// Kills the enemy and the bullet
					}
				}
				if (myEnemies->enemyType.at(i) == 2)
				{
					if (myEnemies->enemyAlive[i] == true	// Checks if the enemies alive, then if the bullets within the enemy
						&& myBullets->playerBulletPosA[b].x < myEnemies->enemyPosition.at(i).x + 42 && myBullets->playerBulletPosA[b].x + 3 > myEnemies->enemyPosition.at(i).x
						&& myBullets->playerBulletPosA[b].y < myEnemies->enemyPosition.at(i).y + 42 && myBullets->playerBulletPosA[b].y + 9 > myEnemies->enemyPosition.at(i).y)
					{
						if (chargeActive)
							myEnemies->enemyHealth.at(i) -= playerDmg * chargePower;
						else
							myEnemies->enemyHealth.at(i) -= playerDmg;
						if (myEnemies->enemyHealth.at(i) <= 0)
							myPlayer->playerScore += 300;
						myBullets->bulletFiredA[b] = false;		// Kills the enemy and the bullet
					}
				}
			}
		}
	}
	//// Player bullets on enemy ship collision END ////

	///////////////////////////////////////////////////////////////////////////////

	//// Enemy bullets on player ship collision START ////
	for (int b = 0; b < myBullets->MAX_ENEMY_BULLETS; b++)
	{
		if (myBullets->enemyBulletFired[b] == true)	// Checks if they're even alive first
		{
			if (myPlayer->shipPos.x - 26 + 9.5f < myBullets->enemyBulletPosA[b].x + 8 && myPlayer->shipPos.x - 26 + 39 - 9.5f > myBullets->enemyBulletPosA[b].x
				&& myPlayer->shipPos.y - 35 < myBullets->enemyBulletPosA[b].y + 8 && myPlayer->shipPos.y - 35 + 36 - 18 > myBullets->enemyBulletPosA[b].y)
			{
				if (mercyInvuln)
				{
					myBullets->enemyBulletFired[b] = false;
				}
				else if (shieldActive)
				{
					myPlayer->playerHealth -= 10 * shieldPower;
					myBullets->enemyBulletFired[b] = false;
				}
				else
				{
					myPlayer->playerHealth -= 10;
					myBullets->enemyBulletFired[b] = false;
				}
			}
		}
	}
	//// Enemy bullets on player ship collision END ////
	
	///////////////////////////////////////////////////////////////////////////////

	//// Player ship on enemy ship collision START ////
	for (int i = 0; i < myEnemies->enemiesMade; i++)	// Player ship on enemy ship collision
	{
		if (myEnemies->enemyType.at(i) == 0)
		{
			if (myEnemies->enemyAlive[i] == true	// Checks if the enemies alive, then if the bullets within the enemy
				&& myPlayer->shipPos.x - 26 + 9.5f < myEnemies->enemyPosition.at(i).x && myPlayer->shipPos.x - 26 + 39 - 9.5f > myEnemies->enemyPosition.at(i).x - 28
				&& myPlayer->shipPos.y - 35 < myEnemies->enemyPosition.at(i).y && myPlayer->shipPos.y - 35 + 36 - 18 > myEnemies->enemyPosition.at(i).y - 26)
			{
				myPlayer->playerHealth -= 1;
			}
		}
		else if (myEnemies->enemyType.at(i) == 1)
		{
			if (myEnemies->enemyAlive[i] == true	// Checks if the enemies alive, then if the bullets within the enemy
				&& myPlayer->shipPos.x - 26 + 9.5f < myEnemies->enemyPosition.at(i).x + 32 && myPlayer->shipPos.x - 26 + 39 - 9.5f > myEnemies->enemyPosition.at(i).x
				&& myPlayer->shipPos.y - 35 < myEnemies->enemyPosition.at(i).y + 25 && myPlayer->shipPos.y - 35 + 36 - 18 > myEnemies->enemyPosition.at(i).y)
			{
				myPlayer->playerHealth -= 1;
			}
		}
		else if (myEnemies->enemyType.at(i) == 2)
		{
			if (myEnemies->enemyAlive[i] == true	// Checks if the enemies alive, then if the bullets within the enemy
				&& myPlayer->shipPos.x - 26 + 9.5f < myEnemies->enemyPosition.at(i).x + 42 && myPlayer->shipPos.x - 26 + 39 - 9.5f > myEnemies->enemyPosition.at(i).x
				&& myPlayer->shipPos.y - 35 < myEnemies->enemyPosition.at(i).y + 42 && myPlayer->shipPos.y - 35 + 36 - 18 > myEnemies->enemyPosition.at(i).y)
			{
				myPlayer->playerHealth -= 1;
			}
		}
	}
	//// Player ship on enemy ship collision END ////

	EnemyFiring();
	CleanBullets();
	w.draw(spellText);
	if (myMode == 3)
	{
		TrainingCollisions();
		//TestWallCollisions();
	}
}

bool Collision::EnemyFiring() {
	if (myMode == 2)
	{
		if (myBullets->timeNow - myBullets->timeAtLastDroneFire >= 1000)
		{
			myBullets->timeAtLastDroneFire = std::clock();
			for (int i = 0; i < myEnemies->enemiesMade; i++)
			{
				if (myEnemies->enemyAlive[i] == true && myEnemies->enemyType[i] == 0)
				{
					for (int b = 0; b < myBullets->MAX_ENEMY_BULLETS; b++)
					{
						if (myBullets->enemyBulletFired[b] == false)
						{
							myBullets->enemyBulletFired[b] = true;
							myBullets->enemyBulletPosA[b] = sf::Vector2f(myEnemies->enemyPosition[i].x - 18, myEnemies->enemyPosition[i].y - 5);
							myBullets->enemyBulletVelocityA[b] = sf::Vector2f(0, 2.5f + myEnemies->enemyVelocity[i].y);
							goto skip;
						}
					}
				}
				else if (myEnemies->enemyAlive[i] == true && myEnemies->enemyType[i] == 1)
				{
					for (int b = 0; b < myBullets->MAX_ENEMY_BULLETS; b++)
					{
						if (myBullets->enemyBulletFired[b] == false)
						{
							myBullets->enemyBulletFired[b] = true;
							myBullets->enemyBulletPosA[b] = sf::Vector2f(myEnemies->enemyPosition[i].x + 12, myEnemies->enemyPosition[i].y + 15);
							float distance = sqrt((myEnemies->enemyPosition[i].x + 12 - (myPlayer->shipPos.x - 26 + 19.5f)) * (myEnemies->enemyPosition[i].x + 12 - (myPlayer->shipPos.x - 26 + 19.5f)) +
								(myEnemies->enemyPosition[i].y + 15 - (myPlayer->shipPos.y - 35 + 7)) * (myEnemies->enemyPosition[i].y + 15 - (myPlayer->shipPos.y - 35 + 7)));
							myBullets->enemyBulletVelocityA[b].x = -5 * ((myEnemies->enemyPosition[i].x + 12 - (myPlayer->shipPos.x - 26 + 19.5f)) / distance);
							myBullets->enemyBulletVelocityA[b].y = -5 * ((myEnemies->enemyPosition[i].y + 15 - (myPlayer->shipPos.y - 35 + 7)) / distance);
							goto skip;
						}
					}
				}
				else if (myEnemies->enemyAlive[i] == true && myEnemies->enemyType[i] == 2)
				{
					for (int s = 0; s < 8; s++)
					{
						for (int b = 0; b < myBullets->MAX_ENEMY_BULLETS; b++)
						{
							if (myBullets->enemyBulletFired[b] == false)
							{
								myBullets->enemyBulletFired[b] = true;
								myBullets->enemyBulletPosA[b] = sf::Vector2f(myEnemies->enemyPosition[i].x + 17, myEnemies->enemyPosition[i].y + 17);
								myBullets->enemyBulletVelocityA[b] = sentryDirections[s];
								goto sentrySkip;
							}
						}
					sentrySkip:;
					}
				}
			skip:;
			}
			return true;
		}
	}
	if (myMode == 3)
	{
		if (myPlayer->shipPos.x > 270)
		{
			if (myBullets->timeNow - myBullets->timeAtLastDroneFire >= 1000)
			{
				myBullets->timeAtLastDroneFire = std::clock();
				for (int i = 0; i < myEnemies->enemiesMade; i++)
				{
					if (myEnemies->enemyAlive[i] == true && myEnemies->enemyType[i] == 0)
					{
						for (int b = 0; b < myBullets->MAX_ENEMY_BULLETS; b++)
						{
							if (myBullets->enemyBulletFired[b] == false)
							{
								myBullets->enemyBulletFired[b] = true;
								myBullets->enemyBulletPosA[b] = sf::Vector2f(myEnemies->enemyPosition[i].x - 18, myEnemies->enemyPosition[i].y - 5);
								myBullets->enemyBulletVelocityA[b] = sf::Vector2f(0, 2.5f);
								goto skip2;
							}
						}
					}
					else if (myEnemies->enemyAlive[i] == true && myEnemies->enemyType[i] == 1)
					{
						for (int b = 0; b < myBullets->MAX_ENEMY_BULLETS; b++)
						{
							if (myBullets->enemyBulletFired[b] == false)
							{
								myBullets->enemyBulletFired[b] = true;
								myBullets->enemyBulletPosA[b] = sf::Vector2f(myEnemies->enemyPosition[i].x + 12, myEnemies->enemyPosition[i].y + 15);
								float distance = sqrt((myEnemies->enemyPosition[i].x + 12 - (myPlayer->shipPos.x - 26 + 19.5f)) * (myEnemies->enemyPosition[i].x + 12 - (myPlayer->shipPos.x - 26 + 19.5f)) +
									(myEnemies->enemyPosition[i].y + 15 - (myPlayer->shipPos.y - 35 + 7)) * (myEnemies->enemyPosition[i].y + 15 - (myPlayer->shipPos.y - 35 + 7)));
								myBullets->enemyBulletVelocityA[b].x = -5 * ((myEnemies->enemyPosition[i].x + 12 - (myPlayer->shipPos.x - 26 + 19.5f)) / distance);
								myBullets->enemyBulletVelocityA[b].y = -5 * ((myEnemies->enemyPosition[i].y + 15 - (myPlayer->shipPos.y - 35 + 7)) / distance);
								goto skip2;
							}
						}
					}
					else if (myEnemies->enemyAlive[i] == true && myEnemies->enemyType[i] == 2)
					{
						for (int s = 0; s < 8; s++)
						{
							for (int b = 0; b < myBullets->MAX_ENEMY_BULLETS; b++)
							{
								if (myBullets->enemyBulletFired[b] == false)
								{
									myBullets->enemyBulletFired[b] = true;
									myBullets->enemyBulletPosA[b] = sf::Vector2f(myEnemies->enemyPosition[i].x + 17, myEnemies->enemyPosition[i].y + 17);
									myBullets->enemyBulletVelocityA[b] = sentryDirections[s];
									goto sentrySkip2;
								}
							}
						sentrySkip2:;
						}
					}
				skip2:;
				}
				return true;
			}
		}
	}
	return true;
}

void Collision::CleanBullets()
{
	for (int i = 0; i < myBullets->MAX_ENEMY_BULLETS; i++)
	{
		if (myBullets->enemyBulletFired[i] == true)
		{
			if (myBullets->enemyBulletPosA[i].x > 660 || myBullets->enemyBulletPosA[i].x < -30 ||
				myBullets->enemyBulletPosA[i].y > 520 || myBullets->enemyBulletPosA[i].y < -20)
				myBullets->enemyBulletFired[i] = false;		// Remove bullets if they are alive and go off-screen
		}
	}
}

void Collision::FireSpell(sf::Event &eve)
{
	std::stringstream ss;
	ss << spells;
	spellString = ss.str();
	spellText.setString("Spells: " + spellString);

	if (eve.type == sf::Event::KeyPressed && (eve.key.code == sf::Keyboard::A || eve.key.code == sf::Keyboard::Left) && spells > 0)
	{
		spells--;
		for (int i = 0; i <= myEnemies->enemiesMade; i++)
		{
			if (myEnemies->enemyAlive[i] == true)
			{
				myEnemies->enemyHealth.at(i) -= blastPower;
				if (myEnemies->enemyHealth.at(i) <= 0)
				{
					if (myEnemies->enemyType.at(i) == 0)
						myPlayer->playerScore += 100;
					if (myEnemies->enemyType.at(i) == 1)
						myPlayer->playerScore += 200;
					if (myEnemies->enemyType.at(i) == 2)
						myPlayer->playerScore += 300;
				}
			}
		}
	}
	if (eve.type == sf::Event::KeyPressed && (eve.key.code == sf::Keyboard::S || eve.key.code == sf::Keyboard::Up) &&
		spells > 0 && chargeActive == false)
	{
		spells--; chargeActive = true;
	}
	if (eve.type == sf::Event::KeyPressed && (eve.key.code == sf::Keyboard::D || eve.key.code == sf::Keyboard::Down) && 
		spells > 0 && shieldActive == false)
	{
		spells--; shieldActive = true;
	}
	if (eve.type == sf::Event::KeyPressed && (eve.key.code == sf::Keyboard::F || eve.key.code == sf::Keyboard::Right) && 
		spells > 0 && mercyInvuln == false)
	{
		spells--; mercyInvuln = true;
	}
}

void Collision::DrawShield(sf::RenderWindow &w)
{
	if (shieldActive)
	{
		shieldSprite.setPosition(sf::Vector2f(myPlayer->shipPos.x - 31, myPlayer->shipPos.y - 40));
		w.draw(shieldSprite);
	}
	if (mercyInvuln)
	{
		invulnSprite.setPosition(sf::Vector2f(myPlayer->shipPos.x - 31, myPlayer->shipPos.y - 40));
		w.draw(invulnSprite);
	}
}

bool Collision::TrainingCollisions()
{
	for (int b = 0; b < myBullets->MAX_PLAYER_BULLETS; b++)	// Cycles through all bullets
	{
		if (myBullets->bulletFiredA[b] == true)	// Checks if they're even alive first
		{
			if (myBullets->playerBulletPosA[b].x < myTest->arrowLeftPos.x + 17 && myBullets->playerBulletPosA[b].x + 3 > myTest->arrowLeftPos.x
				&& myBullets->playerBulletPosA[b].y < myTest->arrowLeftPos.y + 26 && myBullets->playerBulletPosA[b].y + 9 > myTest->arrowLeftPos.y)
			{
				myTest->leftHits += 0.1f;
				myBullets->bulletFiredA[b] = false;
				return true;
			}

			else if (myBullets->playerBulletPosA[b].x < myTest->arrowRightPos.x + 17 && myBullets->playerBulletPosA[b].x + 3 > myTest->arrowRightPos.x
				&& myBullets->playerBulletPosA[b].y < myTest->arrowRightPos.y + 26 && myBullets->playerBulletPosA[b].y + 9 > myTest->arrowRightPos.y)
			{
				myTest->rightHits += 0.1f;
				myBullets->bulletFiredA[b] = false;
				return true;
			}
		}
	}
	return false;
}

bool Collision::TestWallCollisions()
{
	if (myPlayer->shipPos.x - 26 + 39 < 250 + 17 &&
		myPlayer->shipPos.x - 26 + 39 > 250 && 
		myPlayer->shipPos.y - 35 < 200 &&
		myPlayer->shipVelocity.x > 0)
	{
		myPlayer->shipPos.x = 237;
	}


	if (myPlayer->shipPos.x - 26 < 250 + 17 &&
		myPlayer->shipPos.x - 26 > 250 &&
		myPlayer->shipPos.y - 35 < 200 &&
		myPlayer->shipVelocity.x < 0)
	{
		myPlayer->shipPos.x = 291;
	}

	if (myPlayer->shipPos.y - 35 < 200 &&
		myPlayer->shipPos.x - 26 + 39 > 250 &&
		myPlayer->shipPos.x - 26 < 250 + 17 &&
		myPlayer->shipVelocity.y < 0)
	{
		myPlayer->shipPos.y = 235;
	}

	if (myPlayer->shipPos.x - 26 + 39 < 250 + 17 &&
		myPlayer->shipPos.x - 26 + 39 > 250 &&
		myPlayer->shipPos.y - 35 + 36 > 280 &&
		myPlayer->shipVelocity.x > 0)
	{
		myPlayer->shipPos.x = 237;
	}

	if (myPlayer->shipPos.x - 26 < 250 + 17 &&
		myPlayer->shipPos.x - 26 > 250 &&
		myPlayer->shipPos.y - 35 + 36 > 280 &&
		myPlayer->shipVelocity.x < 0)
	{
		myPlayer->shipPos.x = 291;
		return true;
	}

	if (myPlayer->shipPos.y - 35 + 36 > 280 &&
		myPlayer->shipPos.x - 26 + 39 > 250 &&
		myPlayer->shipPos.x - 26 < 250 + 17 &&
		myPlayer->shipVelocity.y > 0)
	{
		myPlayer->shipPos.y = 279;
	}


	return true;
	
	
}
