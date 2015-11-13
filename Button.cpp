#include "Button.h"
//
//I AM REPORT THE HARASS!!
Button::Button() {

}

void Button::Init(sf::Vector2f* pos){
	gd = new GameData();
	btn_Pos = pos;
	current = false;
	btn_Spr = new sf::Sprite();
	btn_texture_notclicked = gd->m_Button1Texture;
	btn_texture_clicked = gd->m_Button2Texture;
	btn_current = btn_texture_notclicked;
	setState(false);// false for not clicked
	btn_Spr->setPosition(*pos);
}

void Button::checkClick(sf::Vector2i mousePos) {
	if (mousePos.x > btn_Pos->x && mousePos.x<(btn_Pos->x + btn_texture_notclicked->getSize().x))//images are the same size
	{
		if (mousePos.y>btn_Pos->y && mousePos.y<(btn_Pos->y + btn_texture_notclicked->getSize().y)) {
			current = !current;
		}
	}
	setState(current);
}



void Button::setState(bool b) {
	if (b){
		btn_current = btn_texture_clicked;
	}
	else{
		btn_current = btn_texture_notclicked;
	}	
}

void Button::exist(sf::RenderWindow &w, sf::Event &eve){
	btn_Spr->setTexture(*btn_current, true);
	w.draw(*btn_Spr);
	while (w.pollEvent(eve)){
		//process mouse/key events in here
		if (eve.type == sf::Event::MouseButtonPressed && eve.type != sf::Event::MouseEntered){
				sf::Vector2i mousePos = sf::Vector2i(eve.mouseButton.x, eve.mouseButton.y);
				checkClick(mousePos);
		}
	}
}

bool Button::sendItUp(){
	return current;
}