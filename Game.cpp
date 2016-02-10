#include"Game.h"

Game::Game(){
	theLevel = new Level(gd);
	clock = new sf::Clock();
	theMenu = new Menu(gd);
	theShop = new Shop();
	back = new sf::Texture();
	back =  (gd.m_lvl1BackGroundTexture);
	theMenu->Init();
	CurrentLevel = 0;
	canReturn = false;
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
		if (canReturn == true){
			if ((eve.type == sf::Event::KeyPressed) && (eve.key.code == sf::Keyboard::Return)){
				theShop->GameStart = 1;
				gameState = SHOP_RUNNING;
			}
		}
		if (gameState == SHOP_RUNNING) { theShop->MuteSounds(eve); }
		if (gameState == GAME_RUNNING) { theLevel->cM->FireSpell(eve); }
		if (gameState != MENU_RUNNING && gameState != SHOP_RUNNING) {
			if (gameState == TRAINING_MODE) { 
				if (thePlayer->ReturnToShop(eve, 3)){
					gameState == SHOP_RUNNING;
				}

			}
		}
		


	}
		switch (gameState){
		case MENU_RUNNING:
		{
			theMenu->Run(w, eve);
			if (theMenu->state() == 2){
				gameState = SHOP_RUNNING;
			}
		}
		break;
		case SHOP_RUNNING:
		{
			theShop->Run(w, eve);
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
				theLevel = new Level(gd);
				theLevel->initLevel(CurrentLevel, theShop);
				theLevel->GetStats(playerStats);
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
				theLevel->GetStats(playerStats);
				thePlayer = new Player(308.5f, 334, playerStats.at(3), playerStats.at(4), playerStats.at(8), playerStats.at(9), theShop->playerScore);
				trainBlt =  new Bullet(300, 300, false, playerStats.at(8), gd);
				trainNMe = new Enemy(2, gd, 0);
				trainingRoom = new Training(trainNMe);
				trainingRoom->musicChannel->setMute(false);
				testCollision = new Collision(trainNMe, trainBlt, thePlayer, trainingRoom, 3, playerStats.at(0),
					playerStats.at(1), playerStats.at(2), playerStats.at(3), playerStats.at(5), playerStats.at(6),
					playerStats.at(7), playerStats.at(10), playerStats.at(11), gd, new LevelOneBoss(gd));
				theShop->musicPlaying = false;
				gameState = TRAINING_MODE;
			}
		}
		break;
		case GAME_RUNNING:
		{
			 
			 if (theLevel->getOver() == false){
				 theLevel->Run(w, p);
				 if (theLevel->getPlayerAlive() == false){
					canReturn = true;
				 }
			 }
			 if ((theLevel->getOver() == true)&&(CurrentLevel < 2)){
				 //CurrentLevel++;
				 //theMenu->Init();
				 theShop->GameStart = 1;
				 gameState = SHOP_RUNNING;
				 theLevel = new Level(gd);
			 }
		}
		break;
		case TRAINING_MODE:
		{
		  trainingRoom->Run(w, eve);
		  trainNMe->Update(3);
		  trainNMe->Draw(w, 3);
		  testCollision->CheckForCollision(w);
		  thePlayer->Update(w, p);
		  testCollision->DrawShield(w);
		  testCollision->TestWallCollisions();
		  thePlayer->Draw(w, 3);				 // Level state
		  trainBlt->Update(w, p);
		  if (thePlayer->state() == 2)
		  {
			  theShop->GameStart = 0;
			  trainingRoom->musicChannel->setMute(true);
			  trainNMe->musicChannel->setMute(true);
			  trainNMe->musicPlaying = false;
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