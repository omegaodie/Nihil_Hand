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

	void Run(sf::RenderWindow &w);

private:
	std::vector<sf::Image*> m_image;//m for menu

	std::vector<sf::Sprite*> m_sprites;

	std::vector<sf::Texture*> m_textures;
	std::vector<Button*> m_Btns;

	float x;
};

#endif 