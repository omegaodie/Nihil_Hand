#ifndef __MENU_H__
#define ___MENU_H__

#include <SFML/Graphics.hpp>
#include "Button.h"


class Menu
{
public:
	Menu();
	~Menu();

	void Init();
	int state();
	void DrawBackground(sf::RenderWindow &w);
	void Run(sf::RenderWindow &w, sf::Event &eve);
	void DrawButtons(sf::RenderWindow &w, sf::Event &eve);

private:
	//std::vector<sf::Image*> m_image;//m for menu
	sf::Image* m_image, *btnClik, *btnNotClik;

	Button *btn1, *btn2;

	//std::vector<sf::Sprite*> m_sprites;
	sf::Sprite*  m_sprite;

	//std::vector<sf::Texture*> m_textures;
	sf::Texture* m_texture;

	std::vector<Button*> m_Btns;

	int exitClick, GameClick;

	float x;
};

#endif 