#include"Game.h"

Game::Game(){
	//the_Enemy = new Enemy(10, 25);
	clock = new sf::Clock();
	theMenu = new Menu();
	//thePlayer = new Player(308.5f, 334);
	//theBullets = new Bullet(300, 300, false);
	theEnemies = new Enemy();
	//theBullets = new Bullet();
	theShop = new Shop();
	//theCollisions = new Collision(theBullets, theEnemies);
	trainingRoom = new Training();
	
	
	theMenu->Init();
	//the_Enemy->Init(*clock);
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
		theShop->MuteSounds(eve);
		if (gameState != MENU_RUNNING && gameState != SHOP_RUNNING) {
			if (gameState == TRAINING_MODE)
			{
				thePlayer->ReturnToShop(eve, 3);
			}
			else
			{
				thePlayer->ReturnToShop(eve, 0);
			}
		}
		


	}
		switch (gameState){
		case MENU_RUNNING:
		{
			theMenu->Run(w, eve);
			if (theMenu->state() == 2){
				//gameState = GAME_RUNNING;
				gameState = SHOP_RUNNING;
			}
		}
		break;
		case SHOP_RUNNING:
		{
			theShop->Run(w, eve);
			//theShop->GetUpgradeStats();
			if (theShop->state() == 2)
			{
				std::vector<float> playerStats = theShop->GetUpgradeStats();
				// OUTPUTTING PLAYER STATS: START
				std::cout << "\nShip made with stats:\nShot Damage: " << playerStats.at(0) <<
					"\nBlast Damage: " << playerStats.at(1) << "\nCharge Bonus: x" << std::setprecision(2) << playerStats.at(2) <<
					"\nShield Defense: " << playerStats.at(3) * 100 << "%\nMaximum HP: " << std::setprecision(3) << playerStats.at(4) <<
					"\nMercy Invuln. (secs): " << std::setprecision(2) << playerStats.at(5) << "\nMaximum Bombs: " << playerStats.at(6) <<
					"\nLucky Endure Rate: " << playerStats.at(7) * 100 << "%\nMove Speed: " << std::setprecision(3) << playerStats.at(8) * 100 <<
					"%\nHitbox Size: " << std::setprecision(2) << playerStats.at(9) * 100 << "%\nDrop Rate: x" << playerStats.at(10) <<
					"\nMagnetism Chance: " << std::setprecision(3) << playerStats.at(11) * 100 << "%" << std::endl;
				// OUTPUTTING PLAYER STATS: FINISH
				thePlayer = new Player(308.5f, 334, playerStats.at(3), playerStats.at(4), playerStats.at(8), playerStats.at(9));
				theBullets = new Bullet(300, 300, false, playerStats.at(8));
				theEnemies = new Enemy(2);
				theCollisions = new Collision(theEnemies, theBullets, thePlayer, playerStats.at(0));
				gameState = GAME_RUNNING;
			}
			if (theShop->state() == 3)
			{
				std::vector<float> playerStats = theShop->GetUpgradeStats();
				// OUTPUTTING PLAYER STATS: START
				std::cout << "\nShip made with stats:\nShot Damage: " << playerStats.at(0) <<
					"\nBlast Damage: " << playerStats.at(1) << "\nCharge Bonus: x" << std::setprecision(2) << playerStats.at(2) <<
					"\nShield Defense: " << playerStats.at(3) * 100 << "%\nMaximum HP: " << std::setprecision(3) << playerStats.at(4) <<
					"\nMercy Invuln. (secs): " << std::setprecision(2) << playerStats.at(5) << "\nMaximum Bombs: " << playerStats.at(6) <<
					"\nLucky Endure Rate: " << playerStats.at(7) * 100 << "%\nMove Speed: " << std::setprecision(3) << playerStats.at(8) * 100 <<
					"%\nHitbox Size: " << std::setprecision(2) << playerStats.at(9) * 100 << "%\nDrop Rate: x" << playerStats.at(10) <<
					"\nMagnetism Chance: " << std::setprecision(3) << playerStats.at(11) * 100 << "%" << std::endl;
				// OUTPUTTING PLAYER STATS: FINISH
				thePlayer = new Player(308.5f, 334, playerStats.at(3), playerStats.at(4), playerStats.at(8), playerStats.at(9));
				theBullets = new Bullet(300, 300, false, playerStats.at(8));
				theEnemies = new Enemy(3);
				theCollisions = new Collision(theEnemies, theBullets, thePlayer, playerStats.at(0));
				trainingRoom->musicChannel->setMute(false);
				gameState = TRAINING_MODE;
			}
		}
		break;
		case GAME_RUNNING:
		{
			//theMenu->DrawBackground(w);
			thePlayer->Update(w, p);
			thePlayer->Draw(w, 0);				 // Level state
			theBullets->Update(w, p);
			theBullets->Draw(w);
			theBullets->HitDetection();
			theEnemies->Update(2);
			theEnemies->Draw(w, 2);
			theCollisions->CheckForCollision();
			if (thePlayer->state() == 2)
			{
				theShop->GameStart = 0;
				gameState = SHOP_RUNNING;
			}
		}
		break;
		case TRAINING_MODE:
		{
			theEnemies->Update(3);
		    theEnemies->Draw(w, 3);
			trainingRoom->Run(w, eve);
			thePlayer->Update(w, p);
			thePlayer->Draw(w, 3);				 // Level state
			theBullets->Update(w, p);
			theBullets->Draw(w);
			theBullets->HitDetection();
			theCollisions->CheckForCollision();
			if (thePlayer->state() == 2)
			{
				theShop->GameStart = 0;
				trainingRoom->musicChannel->setMute(true);
				gameState = SHOP_RUNNING;
			}
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