#include "Button.h"
//
//I AM REPORT THE HARASS!!
Button::Button() {

}

void Button::Init(sf::String s, sf::Vector2f* pos, sf::Image* klik, sf::Image* notklick){
	btn_string = s;
	btn_Pos = pos;
	btn_image_Clicked = klik;
	btn_image_notClicked = notklick;
	current = false;
}

void Button::checkClick(sf::Vector2f mousePos) {
	if (mousePos.x > btn_Pos->x && mousePos.x<(btn_Pos->x + btn_texture->getSize().x))
	{
		if (mousePos.y>btn_Pos->y && mousePos.y<(btn_Pos->y + btn_texture->getSize().y)) {
			current = !current;
		}
	}
	setState(current);
}
void Button::setState(bool b) {
	if (b){
		btn_texture->loadFromImage(*btn_image_Clicked, btn_Box);
	}
	else{
		btn_texture->loadFromImage(*btn_image_notClicked, btn_Box);
	}	
}

void Button::exist(sf::RenderWindow &w){
	btn_Spr->setTexture(*btn_texture, true);
	w.draw(*btn_Spr);
}