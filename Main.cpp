#include <SFML/Graphics.hpp>
#include "Game.h"

int main(){

	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
	Game *the_Game = new Game();

	while (window.isOpen()){

		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		the_Game->Run(window);
		window.display();
	}

}