#include <SFML/Graphics.hpp>
#include "Game.h"

int main(){

	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");//where we draw things
	window.setFramerateLimit(60);
	Game *the_Game = new Game();//our game, everything happens here

	while (window.isOpen()){

		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		the_Game->Run(window);// we are passing  REFERENCE to the window down to the objects they draw on it themselves
		window.display();
	}

}