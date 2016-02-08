#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"


int main(){

	sf::RenderWindow window(sf::VideoMode(920, 1020), "SFML Application");//where we draw things
	window.setFramerateLimit(60);
	Game *the_Game = new Game();//our game, everything happens here
	
	while (window.isOpen()){
		window.clear();
		
		the_Game->Run(window);// we are passing  REFERENCE to the window down to the objects they draw on it themselves
		window.display();
	}

}