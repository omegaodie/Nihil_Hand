#pragma once
#ifndef __SHOP_H__
#define ___SHOP_H__

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include <istream>
#include <sstream>

#include "Button.h"
#include "Player.h"

// FMOD include

#pragma comment(lib, "fmod_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"

class Shop
{
private:
	sf::Texture *buyTexture, *sellTexture, *playTexture, *testTexture, *shopTexture, *currentStatTexture,
		*strengthStatTexture, *intelligenceStatTexture, *vitalityStatTexture,
		*spiritStatTexture, *agilityStatTexture, *luckStatTexture,
		*statLevelTexture, *statBoughtTexture;

	sf::Sprite *buySprite, *sellSprite, *playSprite, *testSprite, *shopSprite, *currentStatSprite,
		*strengthStatSprite, *intelligenceStatSprite, *vitalityStatSprite,
		*spiritStatSprite, *agilityStatSprite, *luckStatSprite,
		*statLevelSprite, *statBoughtSprite;
	
	sf::Font shopFont;
	sf::Text strengthDescText;	// Strength description text
	sf::Text strengthStatsText; // Text for stats in Strength
	sf::Text strengthCostText;	// Cost of next Strength upgrade
	sf::Text intelligenceDescText;
	sf::Text intelligenceStatsText;
	sf::Text intelligenceCostText;
	sf::Text vitalityDescText;
	sf::Text vitalityStatsText;
	sf::Text vitalityCostText;
	sf::Text spiritDescText;
	sf::Text spiritStatsText;
	sf::Text spiritCostText;
	sf::Text agilityDescText;
	sf::Text agilityStatsText;
	sf::Text agilityCostText;
	sf::Text luckDescText;
	sf::Text luckStatsText;
	sf::Text luckCostText;

	sf::Text playerScoreText;
	std::stringstream scoreStream;
	std::string scoreString, strengthString, intelligenceString, vitalityString, spiritString, agilityString, luckString;

	sf::Image *buy_image, *sell_image;

	Button *buyBtn, *sellBtn;

	//Player &myPlayer = Player();

	std::vector<Button*> m_Btns;

	int buyClick, sellClick;

	int statLevels[6];
	int statPrices[6];

	float shotDamage[6], blastDamage[6], chargeBonus[6], shieldDefense[6],
		maxHP[6], mercyInvuln[6], maxBombs[6], luckRate[6],
		moveSpeed[6], hitBoxSize[6], dropRate[6], magnetRange[6];

	std::vector<float> shipStatsVector;

	sf::Vector2f buyBtnPos[6], sellBtnPos[6], statLevelsPos[6], statBoughtPos[36],
		playButtonPos, testButtonPos, shopSpacePos;

	bool statBoughtBool[36];

	FMOD::System *FMODsys;
	FMOD_RESULT result;
	FMOD::Sound *shopMusic, *upgradeSound, *downgradeSound;
	
	bool muteMusicToggle, muteSoundFXToggle, muteReverbToggle, mute3DSoundToggle;
	FMOD::Channel *channel;
	


	void Shop::DrawShop(sf::RenderWindow &w);
	void Shop::DrawButtons(sf::RenderWindow &w, sf::Event &eve);

public:
	int playerScore;

	Shop::Shop();

	void Shop::SetPlayerScore(int points);

	void Shop::Run(sf::RenderWindow &w, sf::Event &eve);

	int Shop::state(); int GameStart;

	void Shop::MuteSounds(sf::Event &eve);
	FMOD::Channel *musicChannel;
	bool musicPlaying, muteMusic, muteSoundFX, muteReverb, mute3DSound;

	void Shop::checkClick(sf::Vector2i mousePos);

	void Shop::CreateShip();

	std::vector<float>& Shop::GetUpgradeStats();
};

#endif