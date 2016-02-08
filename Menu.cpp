#include "Menu.h"

Menu::Menu(const GameData &gdata) : gd(gdata){
}

void Menu::Init(){
	exitClick = 0;
	GameClick = 0;
	m_image = gd.m_MenuBackgroundTexture;
	btnClik = gd.m_Button1Texture;
	btnNotClik = gd.m_Button2Texture;
	m_sprite = new sf::Sprite();
	btn1 = new Button(gd);
	/////this will be replaced by calls to JSonloader////////////
	sf::Vector2f* posBt = new sf::Vector2f(200, 200);
	/////this will be replaced by calls to JSonloader////////////
	btn1->Init("Holo", posBt, btnClik, btnNotClik);
}

void Menu::Run(sf::RenderWindow &w, sf::Event &eve){
	DrawBackground(w);
	DrawButtons(w, eve);
}

int Menu::state(){
	return GameClick;
}

void Menu::DrawBackground(sf::RenderWindow &w){
	//m_texture->loadFromImage(*m_image, sf::IntRect(x, 0, w.getSize().x, w.getSize().y));
	if (x + w.getSize().x < m_image->getSize().x){
		x += 5;
	}
	else{
		x = 0;
	}

	m_sprite->setTexture(*m_image);
	w.draw(*m_sprite);
}

void Menu::DrawButtons(sf::RenderWindow &w, sf::Event &eve){
	btn1->exist(w, eve);
	GameClick = btn1->sendItUp();
}

