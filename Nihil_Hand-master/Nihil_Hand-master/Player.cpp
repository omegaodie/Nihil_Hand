#include "Player.h"

Player::Player()
{
	playerScore = 0;
}

Player::Player(float spawnX, float spawnY, float shieldDef, float HP, float speed, float hitBox, int points)
{
	shipTexture.loadFromFile("resources/shipSheet.png", sf::IntRect(42, 3, 39, 36));
	shipSprite.setTexture(shipTexture);
	shipSprite.setOrigin(26, 35);
	shipPos = sf::Vector2f(spawnX, spawnY);
	shipSpeed = 5.0f * speed;
	playerHealth = HP;
	playerScore = points;

	HUDFont.loadFromFile("C:\\Windows\\Fonts\\OCRAEXT.TTF");
	HUDplayerHealth.setString("HP: 100");
	HUDplayerHealth.setFont(HUDFont);
	HUDplayerHealth.setCharacterSize(16);
	HUDplayerHealth.setColor(sf::Color::White);
	HUDplayerHealth.setPosition(5, 457);

	gameOverTexture.loadFromFile("resources/gameOverText.png");
	gameOverSprite.setTexture(gameOverTexture);
	gameOverSprite.setPosition((640 / 2) - (gameOverTexture.getSize().x / 2), 100);

	gameOverText.setString("Press RETURN to return to the shop.");
	gameOverText.setFont(HUDFont);
	gameOverText.setCharacterSize(16);
	gameOverText.setColor(sf::Color::White);
	gameOverText.setPosition(150, 430);

	HUDplayerScore.setString("Score: 0");
	HUDplayerScore.setFont(HUDFont);
	HUDplayerScore.setCharacterSize(16);
	HUDplayerScore.setColor(sf::Color::White);
	HUDplayerScore.setPosition(500, 457);

	returnToShopText.setString("Press ENTER to enter the shop.");
	returnToShopText.setFont(HUDFont);
	returnToShopText.setCharacterSize(20);
	returnToShopText.setColor(sf::Color::White);
	returnToShopText.setPosition(150, 430);
	drawText = false;

	gameMode = 0;
}

Player::~Player()
{

}

void Player::Update(sf::RenderWindow &w, POINT p)
{
	//std::vector<float> shipStats = myShop.GetUpgradeStats();
	//shipSpeed *= shipStats.at(8);
	dx = (p.x - w.getPosition().x) - shipPos.x;
	dy = (p.y - w.getPosition().y) - shipPos.y;
	float fx = (p.x - w.getPosition().x);
	float fy = (p.y - w.getPosition().y);
	dlength = sqrt((dx*dx) + (dy*dy));
	if (dlength == 0)
		dlength = 0.00000001f;		// Fail-safe to prevent divide by 0 on the next 2 lines
	shipVelocity.x = (dx / dlength) * shipSpeed;
	shipVelocity.y = (dy / dlength) * shipSpeed;
	if (sqrt(((shipPos.x - fx)*(shipPos.x - fx)) + ((shipPos.y - fy)*(shipPos.y - fy))) <= shipSpeed)	// Prevents the ship vibrating around
	{																							// the cursor when close to it
		shipPos = sf::Vector2f(p.x - w.getPosition().x, p.y - w.getPosition().y);
	}
	else shipPos += shipVelocity;	// Get vector between current location and cursor, normalize, and add
	if (shipPos.x < 26)
		shipPos.x = 26;
	if (shipPos.y < 35)
		shipPos.y = 35;
	if (shipPos.x > w.getSize().x - 13)
		shipPos.x = w.getSize().x - 13;
	if (shipPos.y > w.getSize().y)
		shipPos.y = w.getSize().y;		// Prevents ship following cursor out the window
}

void Player::Draw(sf::RenderWindow &w, int mode)
{
	shipSprite.setPosition(shipPos);
	w.draw(shipSprite);

	std::stringstream ss1;
	ss1 << playerHealth;
	healthString = ss1.str();
	HUDplayerHealth.setString("HP: " + healthString);
	w.draw(HUDplayerHealth);

	std::stringstream ss2;
	ss2 << playerScore;
	scoreString = ss2.str();
	HUDplayerScore.setString("Score: " + scoreString);
	w.draw(HUDplayerScore);

	if (mode == 3 && shipPos.x > 0 && shipPos.x < 130 && shipPos.y > 430 && shipPos.y < 430 + 122)
	{
		drawText = true;
	}

	if (drawText == true && mode == 3)
	{
		w.draw(returnToShopText);
		drawText = false;
	}
}

void Player::SetStats(std::vector<float>& myStats)
{
	shipSpeed = 5.0f * myStats.at(8);
	int f = 0;
}

int Player::state(){
	return gameMode;
}

void Player::ReturnToShop(sf::Event &eve, int mode)
{
	if (mode == 3 && eve.type == sf::Event::KeyPressed && eve.key.code == sf::Keyboard::Return &&
		shipPos.x > 0 && shipPos.x < 130 && shipPos.y > 430 && shipPos.y < 430 + 122)
	{
		/*if (muteMusic == false && muteMusicToggle == true)
		{
			musicChannel->setMute(true); muteMusic = true; muteMusicToggle = false;
		}
		if (muteMusic == true && muteMusicToggle == true)
		{
			musicChannel->setMute(false); muteMusic = false; muteMusicToggle = false;
		}*/
		gameMode = 2;
	}
	if (eve.type == sf::Event::KeyReleased && eve.key.code == sf::Keyboard::Return)
	{

	}
		//muteMusicToggle = true;
}

void Player::QuitGameOver(sf::Event &eve)
{

	if (eve.type == sf::Event::KeyPressed && eve.key.code == sf::Keyboard::Return)
	{
		gameMode = 2;
	}
}

void Player::DrawGameOver(sf::RenderWindow &w)
{
	w.draw(gameOverSprite);
	w.draw(gameOverText);
}