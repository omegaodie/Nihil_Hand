#include "Menu.h"

Menu::Menu(const GameData &gdata) :
gd(gdata)
{
}

void Menu::Init()
{
	m_sprite = new sf::Sprite();
	exitClick = 0;
	GameClick = 0;
	m_texture = gd.m_MenuBackgroundTexture;
	btn1 = new Button(gd);
	btn1->Init(new sf::Vector2f(150, 150));
	m_Btns.push_back(btn1);
	m_sprite->setTexture(*m_texture, true);
}

void Menu::Run(sf::RenderWindow &w, sf::Event &eve){
	DrawBackground(w);
	DrawButtons(w, eve);
}

int Menu::state(){
	return GameClick;
}

void Menu::DrawBackground(sf::RenderWindow &w){
	if (m_sprite->getPosition().x + w.getSize().x < m_texture->getSize().x){
		m_sprite->setPosition((sf::Vector2f(m_sprite->getPosition().x + 5, m_sprite->getPosition().y)));
	}
	else{
		m_sprite->setPosition((sf::Vector2f(0, m_sprite->getPosition().y)));
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

