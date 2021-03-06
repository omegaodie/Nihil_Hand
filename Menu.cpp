#include "Menu.h"

Menu::Menu(){
}

void Menu::Init(){
	exitClick = 0;
	GameClick = 0;
	m_image = new sf::Image();
	btnClik = new sf::Image();
	btnNotClik = new sf::Image();
	m_texture = new sf::Texture();
	m_sprite = new sf::Sprite();
	btn1 = new Button();
	/////this will be replaced by calls to JSonloader////////////
	m_image->loadFromFile("resources/image1.jpg");
	btnClik->loadFromFile("resources/isKlick.jpg");
	btnNotClik->loadFromFile("resources/notKlick.png");
	sf::Vector2f* posBt = new sf::Vector2f(200, 200);
	/////this will be replaced by calls to JSonloader////////////
	btn1->Init("Holo", posBt, btnClik, btnNotClik);
	m_Btns.push_back(btn1);
}

void Menu::Run(sf::RenderWindow &w, sf::Event &eve){
	DrawBackground(w);
	DrawButtons(w, eve);
}

int Menu::state(){
	return GameClick;
}

void Menu::DrawBackground(sf::RenderWindow &w){
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

void Menu::DrawButtons(sf::RenderWindow &w, sf::Event &eve){
	for (std::vector<Button*>::iterator it = m_Btns.begin(); it < m_Btns.end(); it++) {
		(*it)->exist(w, eve);
		GameClick = (*it)->sendItUp();
	}
}

