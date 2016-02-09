#include "Enemy.h"

Enemy::Enemy(const GameData &gdata) : gd(gdata){

}

Enemy::Enemy(int mode, const GameData &gdata) : gd(gdata) {
	kills = 0;
	currentWave = 1;
	droneHP = 30;
	sweeperHP = 30;
	sentryHP = 50;
	healthTypes[0] = droneHP; healthTypes[1] = sweeperHP; healthTypes[2] = sentryHP;
	enemiesMade = 0;
	enemyPosition.clear();
	enemyVelocity.clear();
	enemyHealth.clear();
	enemyType.clear();
	enemyWaveSpawns.clear();
	droneOffSet.clear();
	droneSideSpd.clear();
	droneTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(156, 304, 28, 26));
	droneSprite.setTexture(droneTexture);
	droneSprite.setRotation(180);

	HUDSpellTexture.loadFromFile("resources/HUDSpellsTexture.png");
	HUDSideTexture.loadFromFile("resources/sideBar.png");

	HUDSpellSprite.setTexture(HUDSpellTexture); HUDSpellSprite.setPosition(710, 457);
	HUDSideSprite.setTexture(HUDSideTexture); HUDSideSprite.setPosition(640, 0);

	droneSprite.setTexture(droneTexture);
	droneSprite.setRotation(180);


	moneyTexture.loadFromFile("resources/moneyTexture.png");
	moneySprite.setTexture(moneyTexture);

	sweeperTexture.loadFromFile("resources/SweeperTexture.png");
	sweeperSprite.setTexture(sweeperTexture);
	sweeperSprite.setScale(sf::Vector2f(0.25f, 0.25f));

	sentryTexture.loadFromFile("resources/SentryTexture.png");
	sentrySprite.setTexture(sentryTexture);

	

	enemySprites[0] = droneSprite; enemySprites[1] = sweeperSprite; enemySprites[2] = sentrySprite;
	if (mode == 2)
	{
		levelStarted = false;

		for (int i = 0; i < gd.numEnemiesLvLOne; i++)
		{
			enemyPosition.push_back(gd.enemySpawnPosLvLOne.at(i)); // Build vector for enemy spawn positions
			enemyAlive[i] = false;
		}
		droneSideSpd.resize(gd.droneWaveNum);
		droneDis.resize(gd.droneWaveNum);
		droneGroupLength.resize(gd.droneWaveNum);
		droneStartDead.resize(gd.droneWaveNum);
		droneEndDead.resize(gd.droneWaveNum);
		droneMaxOffSet.push_back(50);
		droneFirstEnemy.push_back(0);
		int p = 0;
		int num = 0;
		for (int i = 0, s = 0; i < gd.numWaves; i++)
		{
			vector<sf::Vector2f> dC;
			droneGroupAlive.push_back(gd.waveSizesLvLOne.at(i));
			droneGroupSize.push_back(gd.waveSizesLvLOne.at(i));
			droneGroupStart.push_back(gd.droneSquadStart.at(i));
			num += gd.waveSizesLvLOne.at(i);
			droneFirstEnemy.push_back(num);
			droneGroupSplit.push_back(gd.droneSquadSplit.at(s));
			for (int w = enemiesMade, d = 0; w < enemiesMade + gd.waveSizesLvLOne.at(i); w++, d++)
			{
				enemyVelocity.push_back(gd.enemyWaveVel.at(i));	// Build vector for enemy velocities based on their wave

				if (gd.enemyTypesLvLOne.at(i) == 0)		// If drone type, give enemy health of droneHP
				{
					droneGroupPos.push_back(p); p++;
					enemyHealth.push_back(droneHP);
					enemyType.push_back(0);
					droneSideSpd.at(s) = 2.0f;
					droneGroupNum.push_back(s);
					//droneGroupSplit.push_back(gd->droneSquadSplit.at(s));
					droneDis.at(s) = gd.droneSquadSplit.at(s);
					droneGroupLength.at(s) = gd.droneSquadSplit.at(s) * ((droneGroupSize.at(s) - 1));
					droneStartDead.at(s) = 0;
					droneEndDead.at(s) = 0;
					droneDir[i] = false;
					droneCentered[w] = true;
					droneSide[w] = false;
					dC.push_back(sf::Vector2f(gd.droneSquadStart.at(s) + (droneGroupSplit.at(s) * d), 100));
				}
				if (gd.enemyTypesLvLOne.at(i) == 1)		// if sweeper type, give enemy health of sweeperHP
				{
					enemyHealth.push_back(sweeperHP);
					enemyType.push_back(1);
					droneGroupNum.push_back(s);
					droneGroupPos.push_back(0);
				}
				if (gd.enemyTypesLvLOne.at(i) == 2)		// if sentry type, give enemy health of sentryHP
				{
					enemyHealth.push_back(sentryHP);
					enemyType.push_back(2);
					droneGroupNum.push_back(s);
					droneGroupPos.push_back(0);
				}
			}
			if (gd.enemyTypesLvLOne.at(i) == 0)
			{
				s++;
				droneCentersVec.push_back(dC);
			}
			if (gd.enemyTypesLvLOne.at(i) != 0)
			{
				s++;
				vector<sf::Vector2f> empty;
				droneCentersVec.push_back(empty);
			}
			enemiesMade += gd.waveSizesLvLOne.at(i);	// Keep track of enemies created so far

			enemyWaveSpawns.push_back(gd.waveSpawnTimesLvLOne.at(i));	// Build vector for enemy wave spawn times

			wavesSpawn[i] = false;
			p = 0;
		}
	}

	if (mode == 3)
	{
		pos = { 250, 40 };
		vel = { 0, 0 };
		levelStarted = false;
		enemiesMade = 5;
		droneGroupSplit.push_back(60);
		droneGroupStart.push_back(340);
		droneGroupSize.push_back(enemiesMade);
		droneSideSpd.push_back(1.0f);
		droneMaxOffSet.push_back(40);
		droneDis.push_back(droneGroupSplit.at(0));
		droneFirstEnemy.push_back(0);
		droneStartDead.push_back(0);
		droneEndDead.push_back(0);
		droneGroupAlive.push_back(enemiesMade);
		droneGroupLength.push_back(droneGroupSplit.at(0) * ((droneGroupSize.at(0) - 1)));

		for (int i = 0; i < 100; i++)
		{
			enemyAlive[i] = false;
		}

		for (int i = 0; i < enemiesMade; i++)
		{
			enemyAlive[i] = true;
			enemyPosition.push_back(sf::Vector2f(400 + (droneGroupSplit.at(0) * i), 100));
			enemyHealth.push_back(droneHP);
			enemyType.push_back(0);
			enemyAlive[i] = true;
			droneDir[i] = false;
			droneGroupPos.push_back(i);
			droneCentered[i] = true;
			droneCenters.push_back(sf::Vector2f(droneGroupStart.at(0) + (droneGroupSplit.at(0) * i), 100));
			droneGroupNum.push_back(0);
		}
		droneCentersVec.push_back(droneCenters);

		for (int i = 0; i < gd.numWaves; i++)
		{
			for (int w = enemiesMade; w < enemiesMade + gd.waveSizesLvLOne.at(i); w++)
			{
				enemyVelocity.push_back(gd.enemyWaveVel.at(i));	// Build vector for enemy velocities based on their wave
				if (gd.enemyTypesLvLOne.at(i) == 0)		// If drone type, give enemy health of droneHP
				{
					enemyHealth.push_back(droneHP);
					enemyType.push_back(0);
					droneOffSet.push_back(0);
					droneSideSpd.push_back(2);
				}
				if (gd.enemyTypesLvLOne.at(i) == 1)		// if sweeper type, give enemy health of sweeperHP
				{
					enemyHealth.push_back(sweeperHP);
					enemyType.push_back(1);
				}
				if (gd.enemyTypesLvLOne.at(i) == 2)		// if sentry type, give enemy health of sentryHP
				{
					enemyHealth.push_back(sentryHP);
					enemyType.push_back(2);
				}
			}
			enemiesMade += gd.waveSizesLvLOne.at(i);	// Keep track of enemies created so far
			
			enemyWaveSpawns.push_back(gd.waveSpawnTimesLvLOne.at(i));	// Build vector for enemy wave spawn times

			wavesSpawn[i] = false;
		}

		for (int i = 0; i < 5; i++)
		{
			enemyPosition.at(i) += enemyVelocity.at(i);
			enemyAlive[i] = true;
		}
		enemiesSpawned = 5;
	}

	if (mode == 3)
	{
		pos = { 250, 40 };
		vel = { 0, 0 };
		levelStarted = false;
		enemiesMade = 1;

		for (int i = 0; i < 100; i++)
		{
			enemyAlive[i] = false;
		}

		for (int i = 0; i < enemiesMade; i++)
		{
			//enemyPosition.push_back(sf::Vector2f(390 + (50 * i), 40));
			enemyPosition.push_back(sf::Vector2f(480, 100));
			enemyVelocity.push_back(sf::Vector2f(0, 0));
			enemyHealth.push_back(droneHP);
			enemyType.push_back(0);
			enemyAlive[i] = true;
			droneOffSet.push_back(0);
			droneSideSpd.push_back(2);
			droneDir[i] = true;
		}
		/*FMOD::System_Create(&FMODsys);
		FMODsys->init(100, FMOD_INIT_NORMAL, 0);
		FMODsys->createReverb(&reverb);
		prop1 = FMOD_PRESET_UNDERWATER;
		reverb->setProperties(&prop1);
		FMOD_VECTOR myPos = { 10, 0 };
		FMOD_VECTOR mylisten = { 20, 0 };
		float mindist = 500.0f;
		float maxdist = 500.0f;
		reverb->set3DAttributes(&myPos, mindist, maxdist);
		reverb->setActive(true);
		reverb->setProperties(&prop1);

		reverb->setActive(true);

		//channel->setReverbProperties(
		FMODsys->set3DListenerAttributes(
			0,
			&mylisten,
			&vel,
			0,
			0);
		
		FMODsys->setReverbAmbientProperties(&prop1);
		enemyHumPlaying = false;
		musicPlaying = false;
		result = FMODsys->createSound(
			"resources/EnemyHum.mp3",
			FMOD_LOOP_NORMAL,
			0,
			&enemyHum);
		if (result != FMOD_OK)
			exit(-1);
		if (musicPlaying == false)
		{
			FMODsys->playSound(
				FMOD_CHANNEL_FREE,
				enemyHum,
				false,
				&musicChannel);
			//channel->setReverbProperties(
			//musicChannel->setVolume(0.75f);

			musicPlaying = true;
		}*/
	}
}

Enemy::Enemy(float x, float y, const GameData &gdata) : gd(gdata){
	//e_location = new sf::Vector2f(x, y);*/
}

void Enemy::Init()
{

}

void Enemy::Draw(sf::RenderWindow &w, int mode){// animateion logic here
	//if (mode == 2)
	{
		for (int i = 0; i < enemiesMade; i++)
		{
			if (enemyAlive[i] == true)
			{
				enemySprites[enemyType.at(i)].setPosition(enemyPosition.at(i));
				w.draw(enemySprites[enemyType.at(i)]);
			}
		}
	}
	w.draw(HUDSideSprite);
	w.draw(HUDSpellSprite);
	for (int i = 0; i < 100; i++)
	{
		if (moneyAlive[i])
		{
			moneySprite.setPosition(moneyPos.at(i));
			w.draw(moneySprite);
		}
	}
}

void Enemy::Update(int mode)
{
	if (mode == 2)
	{
		timeNow = std::clock();
		if (levelStarted == false)
		{
			timeAtLastFire = std::clock();
			levelStarted = true;
		}
		
		if (timeNow - timeAtLastFire >= gd.waveSpawnTimesLvLOne.at(currentWave) && wavesSpawn[currentWave] == false)
		{
			wavesSpawn[currentWave] = true;
			for (int i = enemiesSpawned; i < enemiesSpawned + gd.waveSizesLvLOne.at(currentWave); i++)
			{
				enemyAlive[i] = true;
				enemyPosition.at(i) += enemyVelocity.at(i);
			}
			enemiesSpawned += gd.waveSizesLvLOne.at(currentWave);
			if (currentWave < gd.numWaves - 1)
				currentWave++;
		}
		for (int i = 0; i < gd.numEnemiesLvLOne; i++)
		{
			if (enemyHealth.at(i) <= 0)
			{
				enemyAlive[i] = false;
			}
			if (enemyAlive[i] == true)
			{
				enemyPosition.at(i) += enemyVelocity.at(i);
			}
			if (enemyPosition.at(i).x > 750 || enemyPosition.at(i).x < -200 ||
				enemyPosition.at(i).y > 550)
			{
				enemyAlive[i] = false;
			}
		}
	}
	if (mode == 3)
	{
		FMOD_VECTOR sourcePos = { 20, 0, 20 };
		if (musicChannel)
		{
			musicChannel->set3DAttributes(&sourcePos, 0);
		}
		if (musicPlaying == false)
		{
			FMODsys->playSound(
				testMusic,
				0,
				false,
				&musicChannel);
			musicChannel->setVolume(0.75f);
			FMODsys->playSound(
				enemyHum,
				0,
				false,
				&musicChannel);
			//channel->setReverbProperties(
			//musicChannel->setVolume(0.75f);

			musicPlaying = true;
		}
		for (int i = 0, d = 0; i < enemiesMade; i++)
		{
			if (enemyHealth.at(i) <= 0 && enemyAlive[i] == true)
			{
				enemyAlive[i] = false;
				kills++;
			}
			if (enemyType.at(i) == 0)
			{
				droneOffSet.at(d) += droneSideSpd.at(d);
				if (droneOffSet.at(d) >= 125 || droneOffSet.at(d) <= -125)
				{
					droneOffSet.at(d) = 0;
					droneSideSpd.at(d) *= -1;
				}
				enemyPosition.at(i).x += droneSideSpd.at(d);
				d++;
			}
		}
		if (kills >= enemiesMade)
		{
			kills = 0;
			for (int i = 0; i < enemiesMade; i++)
			{
				enemyAlive[i] = true;
				enemyHealth.at(i) = 30;
			}
		}
	}
}

void Enemy::TrainingEnemies(int enemyNum)
{
	enemyPosition.clear();
	enemyVelocity.clear();
	enemyHealth.clear();
	enemyType.clear();
	droneCenters.clear();
	droneGroupPos.clear();
	droneGroupNum.clear();
	droneGroupStart.at(0) = 340;
	droneGroupSplit.at(0) = 60;
	trainingCurrentType = enemyNum;

	for (int i = 0; i < enemiesMade; i++)
	{
		if (enemyNum != 0)
			enemyPosition.push_back(sf::Vector2f(450, 70));
		else
		{
			enemyAlive[i] = true;
			enemyPosition.push_back(sf::Vector2f(400 + (droneGroupSplit.at(0) * i), 100));
			enemyHealth.push_back(droneHP);
			enemyType.push_back(0);
			droneDir[i] = false;
			droneSide[i] = false;
			droneGroupPos.push_back(i);
			droneCentered[i] = true;
			droneCenters.push_back(sf::Vector2f(droneGroupStart.at(0) + (droneGroupSplit.at(0) * i), 100));
			droneGroupNum.push_back(0);
		}
		droneCentersVec.push_back(droneCenters);
		enemyVelocity.push_back(sf::Vector2f(0, 0));
		enemyHealth.push_back(healthTypes[enemyNum]);
		enemyType.push_back(enemyNum);
		enemyAlive[i] = true;
	}
}

void Enemy::DroneCentering(int i)
{
	int s = droneGroupNum.at(i);
	bool resize = false;
	{
		if (i == droneStartDead.at(s) + droneFirstEnemy.at(s) && droneGroupAlive.at(s) >= 5)
		{
			droneGroupLength.at(s) -= droneDis.at(s);
			droneGroupStart.at(s) += droneGroupSplit.at(s);
			droneStartDead.at(s)++;
			for (int d = i, p = 0; p < droneGroupSize.at(s) - 1; d++, p++)
			{
				droneGroupPos.at(d + 1) = p;
				droneCentersVec.at(s).at(p).x = droneGroupStart.at(s) + (droneDis.at(s) * (p));
			}
			resize = true;
		}
		else if (i == droneStartDead.at(s) + droneFirstEnemy.at(s) && droneGroupAlive.at(s) >= 5)
		{
			resize = true;
		}
		else if (i == droneFirstEnemy.at(s) + droneGroupSize.at(s) - droneEndDead.at(s) - 1 && droneGroupAlive.at(s) >= 4)
		{
			droneGroupLength.at(s) -= droneDis.at(s);
			droneEndDead.at(s)++;
			resize = true;
		}
	}

	droneGroupAlive.at(s)--;

	if (resize == false)
	{
		if (droneGroupSize.at(s) == 5)
		{
			if (droneGroupAlive.at(s) == 4)
			{
				droneDis.at(s) = droneGroupLength.at(s) / 3.0;
				if (droneGroupPos.at(i) == 1)
				{
					droneGroupPos.at(i + 1) = 1;
					droneGroupPos.at(i + 2) = 2;
					droneCentersVec.at(s).at(1) = sf::Vector2f(droneGroupStart.at(s) + (droneDis.at(s) * 1), 0);
					droneCentersVec.at(s).at(2) = sf::Vector2f(droneGroupStart.at(s) + (droneDis.at(s) * 2), 0);
					for (int i = droneFirstEnemy.at(s); i < droneFirstEnemy.at(s) + droneGroupSize.at(s); i++)
					{
						droneCentered[i] = false;
					}
				}
				else if (droneGroupPos.at(i) == 2)
				{
					droneGroupPos.at(i + 1) = 2;
					droneCentersVec.at(s).at(1) = sf::Vector2f(droneGroupStart.at(s) + (droneDis.at(s) * 1), 0);
					droneCentersVec.at(s).at(2) = sf::Vector2f(droneGroupStart.at(s) + (droneDis.at(s) * 2), 0);
					for (int i = droneFirstEnemy.at(s); i < droneFirstEnemy.at(s) + droneGroupSize.at(s); i++)
					{
						droneCentered[i] = false;
					}
				}
				else if (droneGroupPos.at(i) == 3)
				{
					droneCentersVec.at(s).at(1) = sf::Vector2f(droneGroupStart.at(s) + (droneDis.at(s) * 1), 0);
					droneCentersVec.at(s).at(2) = sf::Vector2f(droneGroupStart.at(s) + (droneDis.at(s) * 2), 0);
					for (int i = droneFirstEnemy.at(s); i < droneFirstEnemy.at(s) + droneGroupSize.at(s); i++)
					{
						droneCentered[i] = false;
					}
				}
			}
			else if (droneGroupAlive.at(s) == 3)
			{
				droneDis.at(s) = droneGroupLength.at(s) / 2;
				if (droneGroupPos.at(i) == 1)
				{
					int e = droneFirstEnemy.at(s) + 2;
					if (enemyAlive[e] == false)
					{
						droneGroupPos.at(i + 2) = 1;
					}
					else if (enemyAlive[e])
					{
						droneGroupPos.at(i + 1) = 1;
					}
					droneCentersVec.at(s).at(1) = sf::Vector2f(droneGroupStart.at(s) + (droneDis.at(s) * 1), 0);
					for (int i = droneFirstEnemy.at(s); i < droneFirstEnemy.at(s) + droneGroupSize.at(s); i++)
					{
						droneCentered[i] = false;
					}
				}
				else if (droneGroupPos.at(i) == 2)
				{
					int e = droneFirstEnemy.at(s) + 2;
					if (enemyAlive[e] && droneStartDead.at(s) != 0)
					{
						droneGroupPos.at(i + 1 - (droneStartDead.at(s) * 2)) = 1;
					}
					if (enemyAlive[e] == false)
					{
						droneGroupPos.at(i - 2) = 1;
					}
					droneCentersVec.at(s).at(1) = sf::Vector2f(droneGroupStart.at(s) + (droneDis.at(s) * 1), 0);
					for (int i = droneFirstEnemy.at(s); i < droneFirstEnemy.at(s) + droneGroupSize.at(s); i++)
					{
						droneCentered[i] = false;
					}
				}
				else if (droneGroupPos.at(i) == 3)
				{
					droneGroupPos.at(i - 1) = 1;
					droneCentersVec.at(s).at(1) = sf::Vector2f(droneGroupStart.at(s) + (droneDis.at(s) * 1), 0);
					for (int i = droneFirstEnemy.at(s); i < droneFirstEnemy.at(s) + droneGroupSize.at(s); i++)
					{
						droneCentered[i] = false;
					}
				}
			}
		}
		else if (droneGroupSize.at(s) == 4 && droneGroupAlive.at(s) == 3)
		{
			droneDis.at(s) = droneGroupLength.at(s) / 2;
			if (droneGroupPos.at(i) == 1)
			{
				droneGroupPos.at(i + 1) = 1;
				droneCentersVec.at(s).at(1) = sf::Vector2f(droneGroupStart.at(s) + droneDis.at(s), 0);
				for (int i = droneFirstEnemy.at(s); i < droneFirstEnemy.at(s) + droneGroupSize.at(s); i++)
				{
					droneCentered[i] = false;
				}
			}
			else if (droneGroupPos.at(i) == 2)
			{
				droneCentersVec.at(s).at(1) = sf::Vector2f(droneGroupStart.at(s) + droneDis.at(s), 0);
				for (int i = droneFirstEnemy.at(s); i < droneFirstEnemy.at(s) + droneGroupSize.at(s); i++)
				{
					droneCentered[i] = false;
				}
			}
		}
	}
}

void Enemy::DroneStrafe(int squad)
{
	bool atSide = true; // At either of the drone's further points
	for (int i = droneFirstEnemy.at(squad); i < droneFirstEnemy.at(squad) + droneGroupSize.at(squad); i++)
	{
		if (droneSide[i] == false && enemyAlive[i]) { atSide = false; }
	}

	if (droneDir[squad])
	{
		for (int i = droneFirstEnemy.at(squad); i < droneFirstEnemy.at(squad) + droneGroupSize.at(squad); i++)
		{
			if (enemyAlive[i])
			{
				int p = droneGroupPos.at(i);
				enemyPosition.at(i).x += NormVec(sf::Vector2f(droneCentersVec.at(squad).at(p).x + droneMaxOffSet.at(0), 0) - sf::Vector2f(enemyPosition.at(i).x, 0)).x * 0.5f;
				sf::Vector2f vec = sf::Vector2f(droneCentersVec.at(squad).at(p).x + droneMaxOffSet.at(0), 0) - sf::Vector2f(enemyPosition.at(i).x, 0);
				float dis = sqrt((vec.x * vec.x) + (vec.y * vec.y));
				if (dis <= 2)
				{
					enemyPosition.at(i).x = droneCentersVec.at(squad).at(p).x + droneMaxOffSet.at(0);
					droneSide[i] = true;
				}
			}
		}
	}
	if (droneDir[squad] == false)
	{
		for (int i = droneFirstEnemy.at(squad); i < droneFirstEnemy.at(squad) + droneGroupSize.at(squad); i++)
		{
			if (enemyAlive[i])
			{
				int p = droneGroupPos.at(i);
				enemyPosition.at(i).x += NormVec(sf::Vector2f(droneCentersVec.at(squad).at(p).x - droneMaxOffSet.at(0), 0) - sf::Vector2f(enemyPosition.at(i).x, 0)).x * 0.5f;
				sf::Vector2f vec = sf::Vector2f(droneCentersVec.at(squad).at(p).x - droneMaxOffSet.at(0), 0) - sf::Vector2f(enemyPosition.at(i).x, 0);
				float dis = sqrt((vec.x * vec.x) + (vec.y * vec.y));
				if (dis <= 2)
				{
					enemyPosition.at(i).x = droneCentersVec.at(squad).at(p).x - droneMaxOffSet.at(0);
					droneSide[i] = true;
				}
			}
		}
	}

	if (atSide)
	{
		for (int i = droneFirstEnemy.at(squad); i < droneFirstEnemy.at(squad) + droneGroupSize.at(squad); i++)
		{
			if (enemyAlive[i]) { droneSide[i] = false; }
		}
		if (droneDir[squad] == true) { droneDir[squad] = false; }
		else if (droneDir[squad] == false) { droneDir[squad] = true; }
	}
}

void Enemy::DroneToCenters(int squad) {
	for (int i = droneFirstEnemy.at(squad); i < droneFirstEnemy.at(squad) + droneGroupSize.at(squad); i++)
	{
		if (droneCentered[i] == false && enemyAlive[i])
		{
			int p = droneGroupPos.at(i);
			enemyPosition.at(i) += NormVec(sf::Vector2f(droneCentersVec.at(squad).at(p).x, 0) - sf::Vector2f(enemyPosition.at(i).x, 0));
			sf::Vector2f vec = sf::Vector2f(droneCentersVec.at(squad).at(p).x, 0) - sf::Vector2f(enemyPosition.at(i).x, 0);
			float dis = sqrt((vec.x * vec.x) + (vec.y * vec.y));
			if (dis <= 3 && droneCentered[i] == false)
			{
				enemyPosition.at(i).x = droneCentersVec.at(squad).at(p).x;
				droneCentered[i] = true;
			}
		}
	}
}

void Enemy::DroneAI(int squad)
{
	bool centered = true;
	for (int i = droneFirstEnemy.at(squad); i < droneFirstEnemy.at(squad) + droneGroupSize.at(squad); i++)
	{
		if (droneCentered[i] == false && enemyAlive[i] == true) { centered = false; }
	}

	if (centered) // All drones in a squad are orbiting their center
	{
		DroneStrafe(squad);
	}
	else if (centered == false) // Not all drones in a squad are orbiting their center
	{
		DroneToCenters(squad);
	}
}

sf::Vector2f Enemy::NormVec(sf::Vector2f vec)
{
	sf::Vector2f vector;
	float xl = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (xl == 0) { return sf::Vector2f(0, 0); }
	vector = vec / xl;
	return vector;
}