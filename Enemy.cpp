#include "Enemy.h"

Enemy::Enemy(){
	
}

Enemy::Enemy(int mode) {
	gd = new GameData();
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

	sweeperTexture.loadFromFile("resources/SweeperTexture.png");
	sweeperSprite.setTexture(sweeperTexture);
	sweeperSprite.setScale(sf::Vector2f(0.25f, 0.25f));

	sentryTexture.loadFromFile("resources/SentryTexture.png");
	sentrySprite.setTexture(sentryTexture);

	

	enemySprites[0] = droneSprite; enemySprites[1] = sweeperSprite; enemySprites[2] = sentrySprite;
	if (mode == 2)
	{
		levelStarted = false;
		
		for (int i = 0; i < gd->numEnemies; i++)
		{
			enemyPosition.push_back(gd->enemySpawnPos.at(i)); // Build vector for enemy spawn positions
			enemyAlive[i] = false;
		}

		for (int i = 0; i < gd->numWaves; i++)
		{
			for (int w = enemiesMade; w < enemiesMade + gd->waveSizes.at(i); w++)
			{
				enemyVelocity.push_back(gd->enemyWaveVel.at(i));	// Build vector for enemy velocities based on their wave
				if (gd->enemyTypes.at(i) == 0)		// If drone type, give enemy health of droneHP
				{
					enemyHealth.push_back(droneHP);
					enemyType.push_back(0);
					droneOffSet.push_back(0);
					droneSideSpd.push_back(sf::Vector2f(2, 0));
				}
				if (gd->enemyTypes.at(i) == 1)		// if sweeper type, give enemy health of sweeperHP
				{
					enemyHealth.push_back(sweeperHP);
					enemyType.push_back(1);
				}
				if (gd->enemyTypes.at(i) == 2)		// if sentry type, give enemy health of sentryHP
				{
					enemyHealth.push_back(sentryHP);
					enemyType.push_back(2);
				}
			}
			enemiesMade += gd->waveSizes.at(i);	// Keep track of enemies created so far
			
			enemyWaveSpawns.push_back(gd->waveSpawnTimes.at(i));	// Build vector for enemy wave spawn times

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
			droneSideSpd.push_back(sf::Vector2f(2, 0));
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

Enemy::Enemy(float x, float y){
	//e_location = new sf::Vector2f(x, y);*/
}

void Enemy::Init()
{

}

//void Enemy::Init(sf::Clock c){
//	/*e_image = new sf::Image();
//	e_texture = new sf::Texture();
//	e_sprite = new sf::Sprite();
//	e_current_frame = new sf::IntRect();
//	e_image->loadFromFile("resources/runningcat.png");
//	e_sprite_counterX = 0;
//	e_sprite_counterY = 0;
//	timer = c.getElapsedTime().asMilliseconds();*/
//
//}
//
//
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
	/*if (mode == 3)
	{
		for (int i = 0; i < enemiesMade; i++)
		{
			if (enemyAlive[i] == true)
			{
				enemySprites[enemyType.at(i)].setPosition(enemyPosition.at(i));
				w.draw(enemySprites[enemyType.at(i)]);
			}
		}
	}*/
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
		
		if (timeNow - timeAtLastFire >= gd->waveSpawnTimes.at(currentWave) && wavesSpawn[currentWave] == false)
		{
			wavesSpawn[currentWave] = true;
			for (int i = enemiesSpawned; i < enemiesSpawned + gd->waveSizes.at(currentWave); i++)
			{
				enemyAlive[i] = true;
				enemyPosition.at(i) += enemyVelocity.at(i);
			}
			enemiesSpawned += gd->waveSizes.at(currentWave);
			if (currentWave < gd->numWaves - 1)
				currentWave++;
		}
		for (int i = 0; i < gd->numEnemies; i++)
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
		/*if (musicPlaying == false)
		{
			FMODsys->playSound(
				FMOD_CHANNEL_FREE,
				testMusic,
				false,
				&musicChannel);
			musicChannel->setVolume(0.75f);
			FMODsys->playSound(
				FMOD_CHANNEL_FREE,
				enemyHum,
				false,
				&musicChannel);
			//channel->setReverbProperties(
			//musicChannel->setVolume(0.75f);

			musicPlaying = true;
		}*/
		for (int i = 0, d = 0; i < enemiesMade; i++)
		{
			if (enemyHealth.at(i) <= 0 && enemyAlive[i] == true)
			{
				enemyAlive[i] = false;
				kills++;
			}
			if (enemyType.at(i) == 0)
			{
				droneOffSet.at(d) += droneSideSpd.at(d).x;
				if (droneOffSet.at(d) >= 125 || droneOffSet.at(d) <= -125)
				{
					droneOffSet.at(d) = 0;
					droneSideSpd.at(d).x *= -1;
				}
				enemyPosition.at(i) += droneSideSpd.at(d);
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

	for (int i = 0; i < enemiesMade; i++)
	{
		//enemyPosition.push_back(sf::Vector2f(390 + (50 * i), 40));
		if (enemyNum != 0)
			enemyPosition.push_back(sf::Vector2f(450, 70));
		else 
			enemyPosition.push_back(sf::Vector2f(480, 100));
		enemyVelocity.push_back(sf::Vector2f(0, 0));
		enemyHealth.push_back(healthTypes[enemyNum]);
		enemyType.push_back(enemyNum);
		enemyAlive[i] = true;
	}
}

//
//
//void Enemy::Update(sf::Clock c){
//	
//	/*if (timer + 80 < c.getElapsedTime().asMilliseconds()){
//		timer = c.getElapsedTime().asMilliseconds();
//		if (e_sprite_counterX < 1){
//			e_sprite_counterX++;
//		}
//		else{
//			e_sprite_counterX = 0;
//			if (e_sprite_counterY < 2){
//				e_sprite_counterY++;
//			}
//			else{
//				e_sprite_counterY = 0;
//			}
//		}
//	}*/
//	//Animate();
//	//e_texture->loadFromImage(*e_image, *e_current_frame);
//}
//
//void Enemy::Animate(){
//
//	//e_current_frame = new sf::IntRect(e_sprite_counterX * 512, e_sprite_counterY * 256, 512, 256);
//}