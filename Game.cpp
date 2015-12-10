#include"Game.h"

Game::Game(){
	clock = new sf::Clock();
	theMenu = new Menu(gd);
	theLevel = new Level(gd);
	theLevel->initLevel();
	//thePlayer = new Player(308.5f, 334, gd);
	//theBullets = new Bullet(300, 300, false, gd);
	//theEnemies = new Enemy(gd);
	theMenu->Init();
	gameState = MENU_RUNNING;
}
	


void Game::Run(sf::RenderWindow &w){
	sf::Event eve;
	POINT p;
	GetCursorPos(&p);
	while (w.pollEvent(eve))
	{
		// Close window : exit 
		if (eve.type == sf::Event::Closed)
			w.close();

		// Escape key : exit 
		if ((eve.type == sf::Event::KeyPressed) && (eve.key.code == sf::Keyboard::Escape))
			w.close();


	}
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
			 theLevel->Run(w, p);
			//thePlayer->Update(w, p);
			//thePlayer->Draw(w);				 // Level state
			//theBullets->Update(w, p);
			//theBullets->Draw(w);
			//theEnemies->Update();
			//theEnemies->Draw(w);
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