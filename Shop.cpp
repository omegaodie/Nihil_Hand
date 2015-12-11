#include "Shop.h"

Shop::Shop()
{
	
	result = FMOD::System_Create(&FMODsys);

	if (result != FMOD_OK)
	{
		exit(-1);
	}

	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		exit(-1);
	}

	
	result = FMODsys->createStream(
		"resources/ShopTheme.mp3",
		FMOD_DEFAULT,
		0,
		&shopMusic);
	
	if (result != FMOD_OK) {
		exit(-1);
	}

	result = FMODsys->createSound(
		"resources/UpgradeBuy.mp3",
		FMOD_DEFAULT,
		0,
		&upgradeSound);

	if (result != FMOD_OK) {
		exit(-1);
	}

	result = FMODsys->createSound(
		"resources/UpgradeSell.mp3",
		FMOD_DEFAULT,
		0,
		&downgradeSound);

	if (result != FMOD_OK) {
		exit(-1);
	}

	musicPlaying = false;
	shopMusic->setMode(FMOD_LOOP_NORMAL);

	
	shipStatsVector.resize(12);

	shopFont.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	strengthDescText.setString("Strength: All attacks become more powerful.");
	strengthDescText.setFont(shopFont);
	strengthDescText.setCharacterSize(16);
	strengthDescText.setColor(sf::Color::White);
	strengthDescText.setPosition(10, 25);
	strengthStatsText.setString("Shot Damage:\nBlast Damage:");
	strengthStatsText.setFont(shopFont);
	strengthStatsText.setCharacterSize(16);
	strengthStatsText.setColor(sf::Color::White);
	strengthStatsText.setPosition(10, 45);

	intelligenceDescText.setString("Intelligence: Non-offensive Spells become more effective");
	intelligenceDescText.setFont(shopFont);
	intelligenceDescText.setCharacterSize(16);
	intelligenceDescText.setColor(sf::Color::White);
	intelligenceDescText.setPosition(10, 95);
	intelligenceStatsText.setString("Charge Bonus:\nShield Defense:");
	intelligenceStatsText.setFont(shopFont);
	intelligenceStatsText.setCharacterSize(16);
	intelligenceStatsText.setColor(sf::Color::White);
	intelligenceStatsText.setPosition(10, 115);

	vitalityDescText.setString("Vitality: Life capacity and mercy invincibility duration increases.");
	vitalityDescText.setFont(shopFont);
	vitalityDescText.setCharacterSize(16);
	vitalityDescText.setColor(sf::Color::White);
	vitalityDescText.setPosition(10, 165);
	vitalityStatsText.setString("Maximum HP:\nMercy Invuln. (secs):");
	vitalityStatsText.setFont(shopFont);
	vitalityStatsText.setCharacterSize(16);
	vitalityStatsText.setColor(sf::Color::White);
	vitalityStatsText.setPosition(10, 185);

	spiritDescText.setString("Spirit: Spell capacity and chance of surviving a hit with 1 HP increases.");
	spiritDescText.setFont(shopFont);
	spiritDescText.setCharacterSize(16);
	spiritDescText.setColor(sf::Color::White);
	spiritDescText.setPosition(10, 235);
	spiritStatsText.setString("Maximum Bombs:\nLucky Endure Rate:");
	spiritStatsText.setFont(shopFont);
	spiritStatsText.setCharacterSize(16);
	spiritStatsText.setColor(sf::Color::White);
	spiritStatsText.setPosition(10, 255);

	agilityDescText.setString("Agility: Movement speed increases and hitbox size decreases.");
	agilityDescText.setFont(shopFont);
	agilityDescText.setCharacterSize(16);
	agilityDescText.setColor(sf::Color::White);
	agilityDescText.setPosition(10, 305);
	agilityStatsText.setString("Move Speed:\nHitbox Size:");
	agilityStatsText.setFont(shopFont);
	agilityStatsText.setCharacterSize(16);
	agilityStatsText.setColor(sf::Color::White);
	agilityStatsText.setPosition(10, 325);

	luckDescText.setString("Luck: Drop rate increases and items may float towards the player.");
	luckDescText.setFont(shopFont);
	luckDescText.setCharacterSize(16);
	luckDescText.setColor(sf::Color::White);
	luckDescText.setPosition(10, 375);
	luckStatsText.setString("Drop Rate:\nMagnetism Chance:");
	luckStatsText.setFont(shopFont);
	luckStatsText.setCharacterSize(16);
	luckStatsText.setColor(sf::Color::White);
	luckStatsText.setPosition(10, 395);

	playerScoreText.setString("Points: 0");
	playerScoreText.setFont(shopFont);
	playerScoreText.setCharacterSize(20);
	playerScoreText.setColor(sf::Color::White);
	playerScoreText.setPosition(10, 0);

	buy_image = new sf::Image();
	sell_image = new sf::Image();
	buyTexture = new sf::Texture();
	sellTexture = new sf::Texture();
	playTexture = new sf::Texture();
	testTexture = new sf::Texture();

	currentStatTexture = new sf::Texture();
	strengthStatTexture = new sf::Texture();
	intelligenceStatTexture = new sf::Texture();
	vitalityStatTexture = new sf::Texture();
	spiritStatTexture = new sf::Texture();
	agilityStatTexture = new sf::Texture();
	luckStatTexture = new sf::Texture();
	statLevelTexture = new sf::Texture();
	statBoughtTexture = new sf::Texture();

	buySprite = new sf::Sprite();
	sellSprite = new sf::Sprite();
	playSprite = new sf::Sprite();
	testSprite = new sf::Sprite();
	currentStatSprite = new sf::Sprite();
	strengthStatSprite = new sf::Sprite();
	intelligenceStatSprite = new sf::Sprite();
	vitalityStatSprite = new sf::Sprite();
	spiritStatSprite = new sf::Sprite();
	agilityStatSprite = new sf::Sprite();
	luckStatSprite = new sf::Sprite();
	statBoughtSprite = new sf::Sprite();
	statLevelSprite = new sf::Sprite();

	buy_image->loadFromFile("resources/BuyTexture.png");
	sell_image->loadFromFile("resources/SellTexture.png");
	playTexture->loadFromFile("resources/PlayTexture.png");
	testTexture->loadFromFile("resources/TestTexture.png");
	
	currentStatTexture->loadFromFile("resources/CurrentStatTexture.png");
	strengthStatTexture->loadFromFile("resources/StrengthStatTexture.png");
	intelligenceStatTexture->loadFromFile("resources/IntelligenceStatTexture.png");
	vitalityStatTexture->loadFromFile("resources/VitalityStatTexture.png");
	spiritStatTexture->loadFromFile("resources/SpiritStatTexture.png");
	agilityStatTexture->loadFromFile("resources/AgilityStatTexture.png");
	luckStatTexture->loadFromFile("resources/LuckStatTexture.png");

	statLevelTexture->loadFromFile("resources/StatLevelTexture.png");
	statBoughtTexture->loadFromFile("resources/StatBoughtTexture.png");
	sf::Vector2f* buyPos = new sf::Vector2f(480, 50);
	sf::Vector2f* sellPos = new sf::Vector2f(560, 50);

	buyTexture->loadFromImage(*buy_image);
	buySprite->setTexture(*buyTexture);
	buySprite->setPosition(*buyPos);

	sellTexture->loadFromImage(*sell_image);
	sellSprite->setTexture(*sellTexture);
	sellSprite->setPosition(*sellPos);

	playSprite->setTexture(*playTexture);
	playButtonPos = sf::Vector2f(268, 445);
	playSprite->setPosition(playButtonPos);

	testSprite->setTexture(*testTexture);
	testButtonPos = sf::Vector2f(200, 445);
	testSprite->setPosition(testButtonPos);

	currentStatSprite->setTexture(*currentStatTexture);
	currentStatSprite->setPosition(sf::Vector2f(135, 50));

	strengthStatSprite->setTexture(*strengthStatTexture);
	strengthStatSprite->setPosition(sf::Vector2f(0, 50));

	intelligenceStatSprite->setTexture(*intelligenceStatTexture);
	intelligenceStatSprite->setPosition(sf::Vector2f(0, 120));

	vitalityStatSprite->setTexture(*vitalityStatTexture);
	vitalityStatSprite->setPosition(sf::Vector2f(0, 190));

	spiritStatSprite->setTexture(*spiritStatTexture);
	spiritStatSprite->setPosition(sf::Vector2f(0, 260));

	agilityStatSprite->setTexture(*agilityStatTexture);
	agilityStatSprite->setPosition(sf::Vector2f(0, 330));

	luckStatSprite->setTexture(*luckStatTexture);
	luckStatSprite->setPosition(sf::Vector2f(0, 400));

	statLevelSprite->setTexture(*statLevelTexture);

	statBoughtSprite->setTexture(*statBoughtTexture);

	for (int i = 0; i < 6; i++)
	{
		buyBtnPos[i] = sf::Vector2f(485, 48 + (i * 70));
		sellBtnPos[i] = sf::Vector2f(565, 48 + (i * 70));
		statLevelsPos[i] = sf::Vector2f(150, 45 + (i * 70));
		statLevels[i] = 0;
	}
	int t = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int s = 0; s < 6; s++, t++)
		{
			statBoughtPos[t] = sf::Vector2f(150 + (s * 38) + s, 45 + (i * 70));
		}
	}
	//buyBtn->Init("Buy", buyPos, buy_image, buy_image);
	//m_Btns.push_back(buyBtn);
	//sellBtn->Init("Sell", sellPos, sell_image, sell_image);
	//m_Btns.push_back(sellBtn);
	playerScore = 100000;

	statBoughtBool[0] = true;
	statBoughtBool[6] = true;
	statBoughtBool[12] = true;
	statBoughtBool[18] = true;
	statBoughtBool[24] = true;
	statBoughtBool[30] = true;

	for (int i = 0; i < 6; i++)
	{
		shotDamage[i] = 5 + i;
		blastDamage[i] = 50 + (i * 10);
		chargeBonus[i] = 1.5f + (i * 0.1f);
		shieldDefense[i] = (25 + (i * 10)) / 100.0f;
		maxHP[i] = 100 + (i * 20);
		mercyInvuln[i] = 1.0f + (i * 0.2f);
		maxBombs[i] = i;
		luckRate[i] = (i * 10) / 100.0;
		moveSpeed[i] = (100 + (i * 40)) / 100.0f;
		hitBoxSize[i] = (50 - (i * 10)) / 100.0f;
		dropRate[i] = 1.0f + (i * 0.1f);
		magnetChance[i] = (i * 20) / 100.0f;
	}

	GameStart = 0;

	//myPlayer = Player();
	printf("Shop created.\n");
	muteMusic = false; muteSoundFX = false; muteReverb = false; mute3DSound = false;
	muteMusicToggle = true;
}

void Shop::Run(sf::RenderWindow &w, sf::Event &eve){
	DrawShop(w);
	DrawButtons(w, eve);


	if (musicPlaying == false)
	{
		FMODsys->playSound(
			FMOD_CHANNEL_FREE,
			shopMusic,
			false,
			&musicChannel);
		musicChannel->setVolume(0.75f);
		
		musicPlaying = true;
	}
	FMODsys->update();
}

void Shop::MuteSounds(sf::Event &eve)
{
	if (eve.type == sf::Event::KeyPressed && eve.key.code == sf::Keyboard::Num1)
	{
		if (muteMusic == false && muteMusicToggle == true)
		{
			musicChannel->setMute(true); muteMusic = true; muteMusicToggle = false;
		}
		if (muteMusic == true && muteMusicToggle == true)
		{
			musicChannel->setMute(false); muteMusic = false; muteMusicToggle = false;
		}
	}
	if (eve.type == sf::Event::KeyReleased && eve.key.code == sf::Keyboard::Num1)
		muteMusicToggle = true;
}

void Shop::DrawShop(sf::RenderWindow &w)
{
	std::stringstream ss;
	ss << playerScore;
	scoreString = ss.str();
	playerScoreText.setString("Points: " + scoreString);
	w.draw(playerScoreText);
	w.draw(strengthDescText);
	w.draw(strengthStatsText);
	w.draw(intelligenceDescText);
	w.draw(intelligenceStatsText);
	w.draw(vitalityDescText);
	w.draw(vitalityStatsText);
	w.draw(spiritDescText);
	w.draw(spiritStatsText);
	w.draw(agilityDescText);
	w.draw(agilityStatsText);
	w.draw(luckDescText);
	w.draw(luckStatsText);
	/*w.draw(*currentStatSprite);
	w.draw(*strengthStatSprite);
	w.draw(*intelligenceStatSprite);
	w.draw(*vitalityStatSprite);
	w.draw(*spiritStatSprite);
	w.draw(*agilityStatSprite);
	w.draw(*luckStatSprite);*/
	for (int i = 0; i < 6; i++)
	{
		statLevelSprite->setPosition(statLevelsPos[i]);
		w.draw(*statLevelSprite);
	}
	for (int i = 0; i < 36; i++)
	{
		if (statBoughtBool[i] == true)
		{
			statBoughtSprite->setPosition(statBoughtPos[i]);
			w.draw(*statBoughtSprite);
		}
	}
}

void Shop::checkClick(sf::Vector2i mousePos)
{
	for (int i = 0; i < 6; i++)
	{
		if (mousePos.x > buyBtnPos[i].x && mousePos.x < (buyBtnPos[i].x + buyTexture->getSize().x))
		{
			if (mousePos.y > buyBtnPos[i].y && mousePos.y < (buyBtnPos[i].y + buyTexture->getSize().y))
			{
				if (statBoughtBool[5 + (i * 6)] == false && playerScore >= (statLevels[i] + 1) * 1000)
				{
					statLevels[i]++;
					statBoughtBool[(i * 6) + statLevels[i]] = true;
					playerScore -= statLevels[i] * 1000;
					FMODsys->playSound(
						FMOD_CHANNEL_FREE,
						upgradeSound,
						false,
						&channel);
					channel->setVolume(0.6f);				
				}
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (mousePos.x > sellBtnPos[i].x && mousePos.x < (sellBtnPos[i].x + sellTexture->getSize().x))
		{
			if (mousePos.y > sellBtnPos[i].y && mousePos.y < (sellBtnPos[i].y + sellTexture->getSize().y))
			{
				if (statLevels[i] > 0)
				{
					statBoughtBool[(i * 6) + statLevels[i]] = false;
					playerScore += statLevels[i] * 1000;
					statLevels[i]--;
					FMODsys->playSound(
						FMOD_CHANNEL_FREE,
						downgradeSound,
						false,
						&channel);
					channel->setVolume(0.6f);
				}
			}
		}
	}
	if (mousePos.x > playButtonPos.x && mousePos.x < (playButtonPos.x + playTexture->getSize().x))
	{
		if (mousePos.y > playButtonPos.y && mousePos.y < (playButtonPos.y + playTexture->getSize().y))
		{
			GameStart = 2; // Play
			musicChannel->setMute(true);
		}
	}
	if (mousePos.x > testButtonPos.x && mousePos.x < (testButtonPos.x + testTexture->getSize().x))
	{
		if (mousePos.y > testButtonPos.y && mousePos.y < (testButtonPos.y + testTexture->getSize().y))
		{
			GameStart = 3; // Test
			musicChannel->setMute(true);
		}
	}
}

void Shop::DrawButtons(sf::RenderWindow &w, sf::Event &eve)
{
	/*for (std::vector<Button*>::iterator it = m_Btns.begin(); it < m_Btns.end(); it++)
	{
		(*it)->exist(w, eve);
		buyClick = (*it)->sendItUp();
		sellClick = (*it)->sendItUp();
	}*/
	w.draw(*playSprite);
	w.draw(*testSprite);
	for (int i = 0; i < 6; i++)
	{
		buySprite->setPosition(buyBtnPos[i]);
		sellSprite->setPosition(sellBtnPos[i]);
		w.draw(*buySprite);
		w.draw(*sellSprite);
	}
	if (eve.type == sf::Event::MouseButtonPressed && eve.type != sf::Event::MouseEntered){
		sf::Vector2i mousePos = sf::Vector2i(eve.mouseButton.x, eve.mouseButton.y);
		checkClick(mousePos);
	}
}

void Shop::CreateShip()
{
	/*Create ship(shotDamage[statLevels[0]], blastDamage[statLevels[0]],
		chargeBonus[statLevels[1]], shieldDefense[statLevels[1]],
		maxHP[statLevels[2]], mercyInvuln[statLevels[2]],
		maxBombs[statLevels[3]], luckRate[statLevels[3]],
		moveSpeed[statLevels[4]], hitBoxSize[statLevels[4]],
		dropRate[statLevels[5]], magnetChance[statLevels[5]]);*/
}

std::vector<float>& Shop::GetUpgradeStats()
{
	shipStatsVector = { shotDamage[statLevels[0]], blastDamage[statLevels[0]],
		chargeBonus[statLevels[1]], shieldDefense[statLevels[1]],
		maxHP[statLevels[2]], mercyInvuln[statLevels[2]],
		maxBombs[statLevels[3]], luckRate[statLevels[3]],
		moveSpeed[statLevels[4]], hitBoxSize[statLevels[4]],
		dropRate[statLevels[5]], magnetChance[statLevels[5]] };
	return shipStatsVector;
}

int Shop::state(){
	return GameStart;
}