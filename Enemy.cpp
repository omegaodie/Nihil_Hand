#include "Enemy.h"

Enemy::Enemy(){
	levelStarted = false;
	gd = new GameData();
	enemyTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(156, 304, 28, 26));
	enemySprite.setTexture(enemyTexture);
	enemySprite.setRotation(180);
	for (int i = 0; i < 10; i++)
	{
		enemyPosition[i] = sf::Vector2f(gd->enemySpawnWaveOne[i].x + 50, gd->enemySpawnWaveOne[i].y - 30);
		enemyVelocity[i] = sf::Vector2f(0, 3.0f);
		enemyHealth[i] = 40;
		enemyAlive[i] = true;
	}
	kills = 0;
}

Enemy::Enemy(int mode) {
	kills = 0;
	if (mode == 2)
	{
		levelStarted = false;
		gd = new GameData();
		enemyTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(156, 304, 28, 26));
		enemySprite.setTexture(enemyTexture);
		enemySprite.setRotation(180);
		for (int i = 0; i < 10; i++)
		{
			enemyPosition[i] = sf::Vector2f(gd->enemySpawnWaveOne[i].x + 50, gd->enemySpawnWaveOne[i].y - 30);
			enemyVelocity[i] = sf::Vector2f(0, 1.5f);
			enemyHealth[i] = 30;
			enemyAlive[i] = true;
		}
	}

	if (mode == 3)
	{
		pos = { 250, 40 };
		vel = { 0, 0 };
		levelStarted = false;
		enemyTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(156, 304, 28, 26));
		enemySprite.setTexture(enemyTexture);
		enemySprite.setRotation(180);
		for (int i = 0; i < 5; i++)
		{
			enemyPosition[i] = sf::Vector2f(250 + (50 * i), 40);
			enemyVelocity[i] = sf::Vector2f(0, 0);
			enemyHealth[i] = 30;
			enemyAlive[i] = true;
		}
		FMOD::System_Create(&FMODsys);
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
		}
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
	if (mode == 2)
	{
		for (int i = 0; i < 5; i++)
		{
			if (enemyAlive[i] == true)
			{
				enemySprite.setPosition(enemyPosition[i]);
				w.draw(enemySprite);
			}
		}
		if (timeNow - timeAtLastFire > gd->waveTwoSpawnTime)
		{
			for (int i = 5; i < 10; i++)
			{
				if (enemyAlive[i] == true)
				{
					enemySprite.setPosition(enemyPosition[i]);
					w.draw(enemySprite);
				}
			}
		}
	}
	if (mode == 3)
	{
		for (int i = 0; i < 10; i++)
		{
			if (enemyAlive[i] == true)
			{
				enemySprite.setPosition(enemyPosition[i]);
				w.draw(enemySprite);
			}
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
		for (int i = 0; i < 5; i++)
		{
			enemyPosition[i] += enemyVelocity[i];
		}
		if (timeNow - timeAtLastFire >= gd->waveTwoSpawnTime)
		{
			for (int i = 5; i < 10; i++)
			{
				enemyPosition[i] += enemyVelocity[i];
			}
		}
		for (int i = 0; i < 10; i++)
		{
			if (enemyPosition[i].y > 600)
			{
				enemyPosition[i].y = -30;
				enemyAlive[i] = true;
				enemyHealth[i] = 40;
			}
			if (enemyHealth[i] <= 0)
				enemyAlive[i] = false;
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
		for (int i = 0; i < 5; i++)
		{
			if (enemyHealth[i] <= 0 && enemyAlive[i] == true)
			{
				enemyAlive[i] = false;
				kills++;
			}
		}
		if (kills >= 5)
		{
			kills = 0;
			for (int i = 0; i < 5; i++)
			{
				enemyAlive[i] = true;
				enemyHealth[i] = 30;
			}
		}
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