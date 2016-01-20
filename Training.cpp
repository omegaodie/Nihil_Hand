#include "Training.h"

Training::Training(Enemy* enemy)
{
	myEnemy = enemy;
	shopTexture.loadFromFile("resources/ShopReturnTexture.png");
	shopSpr.setTexture(shopTexture);
	shopSpr.setScale(sf::Vector2f(0.5f, 0.5f));
	shopAreaPos = sf::Vector2f(0, 370);
	shopSpr.setPosition(shopAreaPos);

	testFloorTexture.loadFromFile("resources/TestFloorTexture.png");
	testFloorSpr.setTexture(testFloorTexture);
	testFloorSpr.setPosition(340, 0);

	wallDownTexture.loadFromFile("resources/WallDownTexture.png");
	wallDownSpr.setTexture(wallDownTexture);
	wallDownSpr.setPosition(330, 0);

	wallUpTexture.loadFromFile("resources/WallUpTexture.png");
	wallUpSpr.setTexture(wallUpTexture);
	wallUpSpr.setPosition(330, 280);

	arrowRightTexture.loadFromFile("resources/ArrowRightTexture.png");
	arrowRightSpr.setTexture(arrowRightTexture);
	arrowRightPos = sf::Vector2f(102, 30);
	arrowRightSpr.setPosition(arrowRightPos);
	rightHits = 0;

	arrowLeftTexture.loadFromFile("resources/ArrowLeftTexture.png");
	arrowLeftSpr.setTexture(arrowLeftTexture);
	arrowLeftPos = sf::Vector2f(40, 30);
	arrowLeftSpr.setPosition(arrowLeftPos);
	leftHits = 0;

	droneTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(156, 304, 28, 26));
	droneSpr.setTexture(droneTexture);
	myEnemy->droneSprite.setPosition(92, 58);

	sweeperTexture.loadFromFile("resources/SweeperTexture.png");
	sweeperSpr.setTexture(sweeperTexture);
	myEnemy->sweeperSprite.setScale(sf::Vector2f(0.25f, 0.25f));
	myEnemy->sweeperSprite.setPosition(64, 30);

	sentryTexture.loadFromFile("resources/SentryTexture.png");
	sentrySpr.setTexture(sentryTexture);
	myEnemy->sentrySprite.setPosition(58, 24);

	currentEnemy = 0;
	enemyDisplaySpr[0] = myEnemy->droneSprite; enemyDisplaySpr[1] = myEnemy->sweeperSprite; enemyDisplaySpr[2] = myEnemy->sentrySprite;

	result = FMOD::System_Create(&FMODsys);
	if (result != FMOD_OK) { exit(-1); }
	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) { exit(-1); }

	result = FMODsys->createStream(
		"resources/TestMusic.mp3",
		FMOD_LOOP_NORMAL,
		0,
		&trainingMusic);
	if (result != FMOD_OK) { exit(-1); }
	musicPlaying = false;
}

Training::~Training()
{
	
}

void Training::Run(sf::RenderWindow &w, sf::Event &eve)
{
	if (musicPlaying == false)
	{
		FMODsys->playSound(
			FMOD_CHANNEL_FREE,
			trainingMusic,
			false,
			&musicChannel);
		musicChannel->setVolume(0.75f);

		musicPlaying = true;
	}
	Draw(w);

	

	if (leftHits >= 2)
	{
		leftHits = 0;
		currentEnemy--;
		if (currentEnemy < 0)
			currentEnemy = 2;
		myEnemy->TrainingEnemies(currentEnemy);

	}
	if (rightHits >= 2)
	{
		rightHits = 0;
		currentEnemy++;
		if (currentEnemy > 2)
			currentEnemy = 0;
		myEnemy->TrainingEnemies(currentEnemy);
	}	

	arrowLeftPos = sf::Vector2f(40 - leftHits, arrowLeftPos.y);
	arrowRightPos = sf::Vector2f(102 + rightHits, arrowRightPos.y);

	arrowLeftSpr.setPosition(arrowLeftPos);
	arrowRightSpr.setPosition(arrowRightPos);
}

void Training::Draw(sf::RenderWindow &w)
{
	w.draw(testFloorSpr);
	w.draw(wallDownSpr);
	w.draw(wallUpSpr);
	w.draw(shopSpr);
	w.draw(arrowRightSpr);
	w.draw(arrowLeftSpr);
	w.draw(enemyDisplaySpr[currentEnemy]);
}