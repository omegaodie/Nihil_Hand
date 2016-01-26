//not my own work but it's just a button for the menu and doesnt constitute core gameplay surely
// source: http://en.sfml-dev.org/forums/index.php?topic=5950.0
// owner: asdatapel
//i've made it better though, don't like what he did at all really
#pragma once
#ifndef __BUTTON_H__
#define ___BUTTON_H__

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "GameData.h"

class Button {
public:
	Button(const GameData &);
	void Init(sf::String s, sf::Vector2f* pos, sf::Texture* klik, sf::Texture* notklick);
	void checkClick(sf::Vector2i);
	void setState(bool b);
	int sendItUp();
	void exist(sf::RenderWindow &w, sf::Event &eve);
	const GameData& gd;
private:
	sf::Sprite* btn_Spr;
	sf::Vector2f* btn_Pos;
	sf::Texture* btn_image_notClicked;
	sf::Texture* btn_image_Clicked;
	sf::String btn_string;

	bool current;
};
#endif