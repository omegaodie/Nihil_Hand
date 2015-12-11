#include "Training.h"

Training::Training()
{
	shopTexture.loadFromFile("resources/ShopReturnTexture.png");
	shopSprite.setTexture(shopTexture);
	shopSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	shopAreaPos = sf::Vector2f(0, 370);
	shopSprite.setPosition(shopAreaPos);

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
}

void Training::Draw(sf::RenderWindow &w)
{
	w.draw(shopSprite);
}