//not my own work but it's just a button for the menu and doesnt constitute core gameplay surely
// source: http://en.sfml-dev.org/forums/index.php?topic=5950.0
// owner: asdatapel
//i've made it better though, don't like what he did at all really
#ifndef __BUTTON_H__
#define ___BUTTON_H__

#include <SFML/Graphics.hpp>
#include "GameData.h"

class Button {
public:
	Button(const GameData & gdata);
	void Init(sf::Vector2f* pos);
	void checkClick(sf::Vector2i);
	void setState(bool b);
	bool sendItUp();
	void exist(sf::RenderWindow &w, sf::Event &eve);
private:
	const GameData& gd;
	sf::Sprite* btn_Spr;
	sf::Vector2f* btn_Pos;
	sf::Texture* btn_texture_notclicked;
	sf::Texture* btn_texture_clicked;
	sf::Texture* btn_current;

	bool current;
};
#endif