#include "Button.h"
//
//I AM REPORT THE HARASS!!
Button::Button(const GameData &gdata) : gd(gdata) {

}

void Button::Init(sf::String s, sf::Vector2f* pos, sf::Texture* klik, sf::Texture* notklick){
	btn_string = s;
	btn_Pos = pos;
	btn_image_Clicked = klik;
	btn_image_notClicked = notklick;
	current = false;
	btn_Spr = new sf::Sprite();
	setState(false);// false for not clicked
	btn_Spr->setPosition(*pos);
}

void Button::checkClick(sf::Vector2i mousePos) {
	if (mousePos.x > btn_Pos->x && mousePos.x<(btn_Pos->x + 256))
	{
		if (mousePos.y>btn_Pos->y && mousePos.y<(btn_Pos->y + 256)) {
			current = !current;
		}
	}
	setState(current);
}



void Button::setState(bool b) {
	if (b){
		btn_Spr->setTexture(*btn_image_notClicked);
	}
	else{
		btn_Spr->setTexture(*btn_image_Clicked);
		//transition fade here
	}	
}

void Button::exist(sf::RenderWindow &w, sf::Event &eve){
	w.draw(*btn_Spr);
	if (eve.type == sf::Event::MouseButtonPressed && eve.type != sf::Event::MouseEntered){
		sf::Vector2i mousePos = sf::Vector2i(eve.mouseButton.x, eve.mouseButton.y);
		checkClick(mousePos);
	}
}

int Button::sendItUp(){
	if (current == false){
		return 0;
	}
	else{
		return 2;
	}
}