#include "Rocket.h"

Rocket::Rocket(const GameData &gdata) : gd(gdata) {
	rSprite = new sf::Sprite();
	rAlive = false;
	rVelocityOne = new sf::Vector2f(0, 1.5);
	rVelocityTwo = new sf::Vector2f(0, 2.5);
	rPosition = sf::Vector2f();
	countdown = 100;
	//rPosition = new sf::
}

void Rocket::Init(sf::Vector2f bPos, int ft) {
	rAlive = true;
	dieSwitch = 0;
	rFlightTexture = gd.m_RocketFlightTexture;
	for (int i = 0; i < 81; i++) {
		rExplosionTextures[i] = gd.m_RocketAnimTextures[i];
	}
	frame = 0;
	rSprite->setTexture(*rFlightTexture);
	//rSprite->setTexture(*rExplosionTextures[frame]);
	rPosition = bPos;
	rSprite->setPosition(rPosition);
	rSprite->setOrigin(rFlightTexture->getSize().x / 2, rFlightTexture->getSize().y / 2);
	timeAtFired = time.getElapsedTime().asMilliseconds();
	actualLocation = new sf::Vector2f();
	r_CurrentRadius = 0.75;
	r_PosOnRadius = 5;
	r_Theta = 0;
	fireType = ft;
}

void Rocket::Draw(sf::RenderWindow &w) {
	if (dieSwitch != 1) {
		//Animate();
		w.draw(*rSprite);
	}
	else {
		if (frame < 81){
			Animate();
			w.draw(*rSprite);
		}
		else{
			rAlive = false;
			new Rocket(gd);
		}
	}
}

void Rocket::update() {
	if ((rAlive) && (dieSwitch != 1)){
		if (fireType == 1) {
			rPosition.y += rVelocityOne->y;
			r_PosOnRadius -= incrementA;
			r_CurrentRadius += incrementB;
			if (r_Theta < 10) {
				incrementA = 0.05;
				incrementB = 0.5;
				r_Theta += 0.1;
			}
			else if (r_Theta < 20) {
				r_Theta += 0.05;
				incrementA = 0.25;
				incrementB = 0.25;
			}
			else if ((r_Theta < 60) && (dieSwitch != 1)) {
				dieSwitch = 1;
				timeAtFired = time.getElapsedTime().asMilliseconds();
				rSprite = new sf::Sprite();
				rSprite->setOrigin(rExplosionTextures[0]->getSize().x / 2,
					rExplosionTextures[0]->getSize().y / 2);
				rSprite->setTexture(*rExplosionTextures[frame]);
			}
			deltaTime = time.getElapsedTime().asMilliseconds() - timeAtFired;
			actualLocation->x = rPosition.x + (((r_CurrentRadius + r_PosOnRadius) * r_Theta) * cos(r_Theta));
			actualLocation->y = rPosition.y + (((r_CurrentRadius + r_PosOnRadius) * r_Theta) * sin(r_Theta));
			rSprite->setPosition(*actualLocation);
			rSprite->setRotation((r_Theta * r_Theta * 15) + 90);
		}
		else {
			if (rPosition.y < 720) {
				rSprite->setRotation(180);
				rPosition.y += rVelocityTwo->y;
				rSprite->setPosition(rPosition);
			}
			else {
				dieSwitch = 1;
				timeAtFired = time.getElapsedTime().asMilliseconds();
				rSprite = new sf::Sprite();
				rSprite->setOrigin(rExplosionTextures[0]->getSize().x / 2,
					rExplosionTextures[0]->getSize().y / 2);
				rSprite->setPosition(rPosition);
				rSprite->setTexture(*rExplosionTextures[frame]);
			}
		}
	}
}


void Rocket::RandomlyExplode(){
	dieSwitch = 1;
}

void Rocket::Animate()
{
	if (timeAtFired + 20 < time.getElapsedTime().asMilliseconds()) {
		timeAtFired = time.getElapsedTime().asMilliseconds();
		if (frame < 81) {
			frame++;
			rSprite->setTexture(*rExplosionTextures[frame]);
		}
		else {
			rAlive = false;
			frame = 0;
			rSprite->setTexture(*rExplosionTextures[0]);
		}
	}
}

void Rocket::FlightTime()
{
	/*if (dieSwitch == 1) {
	countdown--;
	}*/
}

bool Rocket::getAlive()
{
	return rAlive;
}


sf::Vector2f Rocket::getPosition(){
	return rPosition;
}