#include"Game.h"

Game::Game(){
	//the_Enemy = new Enemy(10, 25);
	clock = new sf::Clock();
	theMenu = new Menu();
	thePlayer = new Player(308.5f, 334);
	theBullets = new Bullet(300, 300, false);
	theEnemies = new Enemy();
	
	theMenu->Init();
	//the_Enemy->Init(*clock);
	gameState = MENU_RUNNING;
}
	


void Game::Run(sf::RenderWindow &w){
	sf::Event eve;
	POINT p;
	GetCursorPos(&p);
		switch (gameState){
		case MENU_RUNNING:
		{
			theMenu->Run(w, eve);
			if (theMenu->state() == 1){
				gameState = GAME_RUNNING;
			}
		}
		break;
		case GAME_RUNNING:
		{
			theMenu->DrawBackground(w);
			thePlayer->Update(w, p);
			thePlayer->Draw(w);				 // Level state
			theBullets->Update(w, p);
			theBullets->Draw(w);
			theEnemies->Update();
			theEnemies->Draw(w);
		}
		break;
		case END:
		{
			w.close();
			// End state
		}
			break;
		}
	
}