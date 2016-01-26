#include"Game.h"

Game::Game(){
	//the_Enemy = new Enemy(10, 25);
	clock = new sf::Clock();
	theMenu = new Menu(gd);
	thePlayer = new Player();
	Boss = new LevelOneBoss(gd);
	Boss->Init();
	//thePlayer = new Player(308.5f, 334);
	//theBullets = new Bullet(300, 300, false);
	theEnemies = new Enemy(gd);
	//theBullets = new Bullet();
	theShop = new Shop();
	//theCollisions = new Collision(theBullets, theEnemies);
	//trainingRoom = new Training(theEnemies);
	
	back = new sf::Texture();
	back =  (gd.m_lvl1BackGroundTexture);
	
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
		if (gameState == SHOP_RUNNING) { theShop->MuteSounds(eve); }
		if (gameState == GAME_RUNNING || gameState == TRAINING_MODE) { theCollisions->FireSpell(eve); }
		if (gameState != MENU_RUNNING && gameState != SHOP_RUNNING) {
			if (thePlayer->playerHealth <= 0) { thePlayer->QuitGameOver(eve); }
			if (gameState == TRAINING_MODE) { thePlayer->ReturnToShop(eve, 3); }
			else { thePlayer->ReturnToShop(eve, 0); }
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
				thePlayer = new Player(308.5f, 334, playerStats.at(3), playerStats.at(4), playerStats.at(8), playerStats.at(9), theShop->playerScore);
				theBullets = new Bullet(300, 300, false, playerStats.at(8));
				theEnemies = new Enemy(2, gd);
				theCollisions = new Collision(theEnemies, theBullets, thePlayer, trainingRoom, 2, playerStats.at(0), 
					playerStats.at(1), playerStats.at(2), playerStats.at(3), playerStats.at(5), playerStats.at(6));
				theShop->musicPlaying = false;
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
				thePlayer = new Player(308.5f, 334, playerStats.at(3), playerStats.at(4), playerStats.at(8), playerStats.at(9), theShop->playerScore);
				theBullets = new Bullet(300, 300, false, playerStats.at(8));
				theEnemies = new Enemy(3, gd);
				trainingRoom = new Training(theEnemies);
				trainingRoom->musicChannel->setMute(false);
				theCollisions = new Collision(theEnemies, theBullets, thePlayer, trainingRoom, 3, playerStats.at(0),
					playerStats.at(1), playerStats.at(2), playerStats.at(3), playerStats.at(5), playerStats.at(6));
				theShop->musicPlaying = false;
				gameState = TRAINING_MODE;
			}
		}
		break;
		case GAME_RUNNING:
		{
			if (Boss->getAlive()) {
				Boss->update(w);
				///return bool for restart/next level
			}
			if (thePlayer->playerHealth > 0)
			{
				//theBullets->Update(w, p);
				//theEnemies->Update(2);
				//theEnemies->Draw(w, 2);
				theCollisions->CheckForCollision(w);
				thePlayer->Update(w, p);
				thePlayer->Draw(w, 0);				 // Level state
			}
			if (thePlayer->playerHealth <= 0) { thePlayer->DrawGameOver(w); }
			if (thePlayer->state() == 2)
			{
				theShop->SetPlayerScore(thePlayer->playerScore);
				theShop->GameStart = 0;
				//theShop->musicChannel->setMute(false);
				gameState = SHOP_RUNNING;
			}
		}
		break;
		case TRAINING_MODE:
		{
			trainingRoom->Run(w, eve);
			theEnemies->Update(3);
		    theEnemies->Draw(w, 3);
			theCollisions->CheckForCollision(w);
			thePlayer->Update(w, p);
			theCollisions->DrawShield(w);
			theCollisions->TestWallCollisions();
			thePlayer->Draw(w, 3);				 // Level state
			theBullets->Update(w, p);
			if (thePlayer->state() == 2)
			{
				theShop->GameStart = 0;
				trainingRoom->musicChannel->setMute(true);
				theEnemies->musicChannel->setMute(true);
				theEnemies->musicPlaying = false;
				theShop->SetPlayerScore(thePlayer->playerScore);
				theShop->musicChannel->setMute(false);
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