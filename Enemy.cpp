#include "Enemy.h"

Enemy::Enemy(){
	levelStarted = false;
	gd = new GameData();
	bullet = new Bullet();
	enemySprite = new sf::Sprite();
	enemyTexture = gd->m_EnemyTexture;
	//enemyTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(156, 304, 28, 26));
	enemySprite->setTexture(*enemyTexture);
	enemySprite->setRotation(180);
	for (int i = 0; i < 10; i++)
	{
		enemyPosition[i] = sf::Vector2f(gd->enemySpawnWaveOne[i].x + 50, gd->enemySpawnWaveOne[i].y - 30);
		enemyVelocity[i] = sf::Vector2f(0, 3.0f);
		enemyAlive[i] = true;
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
void Enemy::Draw(sf::RenderWindow &w){// animateion logic here
	for (int i = 0; i < 5; i++)
	{
		if (enemyAlive[i] == true)
		{
			enemySprite->setPosition(enemyPosition[i]);
			w.draw(*enemySprite);
		}
	}
	if (timeNow - timeAtLastFire > gd->waveTwoSpawnTime)
	{
		for (int i = 5; i < 10; i++)
		{
			if (enemyAlive[i] == true)
			{
				enemySprite->setPosition(enemyPosition[i]);
				w.draw(*enemySprite);
			}
		}
	}
}

void Enemy::Update()
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
	HitDetection();
}

void Enemy::HitDetection()
{
	
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