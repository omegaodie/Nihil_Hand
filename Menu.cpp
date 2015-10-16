#include "Menu.h"

Menu::Menu(){
}

void Menu::Init(){
	m_image = new sf::Image();
	m_texture = new sf::Texture();
	m_sprite = new sf::Sprite();
	m_image->loadFromFile("resources/image1.jpg");


}

void Menu::Run(sf::RenderWindow &w){
	m_texture->loadFromImage(*m_image, sf::IntRect(x, 0, w.getSize().x, w.getSize().y));
	if (x + w.getSize().x < m_image->getSize().x){
		x += 5;
	}
	else{
		x = 0;
	}
	
	m_sprite->setTexture(*m_texture, true);
	w.draw(*m_sprite);
}


