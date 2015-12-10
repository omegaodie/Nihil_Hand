#include "Enemy.h"


Enemy::Enemy(const GameData &gdata, int i) : gd(gdata){
	levelStarted = false;
	
	timeNow = 0;
	enemySprite = new sf::Sprite();
	enemyTexture = gd.m_EnemyTexture;
	enemySprite->setTexture(*enemyTexture);
	enemySprite->setRotation(180);
	enemyPosition = sf::Vector2f(gd.enemySpawnWaveOne[i].x + 50, gd.enemySpawnWaveOne[i].y - 30);
	enemyVelocity = sf::Vector2f(0, 0.50f);
	enemyAlive = true;
	theBullets = new Bullet(gdata, enemyPosition.x, enemyPosition.y, false);
}

void Enemy::FireBullets(){
	theBullets->FireBullet(enemyPosition);
}

sf::Vector2f* Enemy::GetPos(){
	return &enemyPosition;
}


void Enemy::Init()
{

}


void Enemy::Draw(sf::RenderWindow &w){// animateion logic here
	if (enemyAlive == true)
	{
		enemySprite->setPosition(enemyPosition);
			w.draw(*enemySprite);
		}
	if (timeNow - timeAtLastFire > gd.waveTwoSpawnTime)
	{
		if (enemyAlive == true)
		{
			enemySprite->setPosition(enemyPosition);
			w.draw(*enemySprite);
		}
	}
}

void Enemy::Update(sf::Clock c)
{
	timeNow = c.getElapsedTime().asMilliseconds();
	if (levelStarted == false)
	{
		timeAtLastFire = 0;
		levelStarted = true;
	}
	enemyPosition += enemyVelocity;

	if (timeNow - timeAtLastFire >= gd.waveTwoSpawnTime)
	{
		enemyPosition += enemyVelocity;
	}
}
