#include "Rocket.h"

Rocket::Rocket(const GameData &gdata) : gd(gdata) {
	rSprite = new sf::Sprite();
	rAlive = false;
	rVelocity = new sf::Vector2f(0, 0.5);
	rPosition = new sf::Vector2f();
	//rPosition = new sf::
}

void Rocket::Init(sf::Vector2f *bPos, int ft) {
	rAlive = true;
	dieSwitch = 0;
	rFlightTexture = gd.m_RocketFlightTexture;
	for (int i = 0; i < 6; i++) {
		rExplosionTextures[i] = gd.m_RocketAnimTextures[i];
	}
	frame = 0;
	rSprite->setTexture(*rFlightTexture);
	//rSprite->setTexture(*rExplosionTextures[frame]);
	rPosition = bPos;
	rSprite->setPosition(*rPosition);
	
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
	}else {
		if (frame < 6){
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
	// a b angle increment
	//x=(a+b*angle)*cos(angle),//
	//y=(a+b*angle)*sin(angle)
	////////////////////NEEDDSSSSS WORKKKKKKK||||||||||||||||||||||||||||||||||||||||||||||
	if (rAlive) {
		if (fireType == 1) {
			rPosition->y += rVelocity->y;
			r_PosOnRadius -= incrementA;
			r_CurrentRadius += incrementB;
			//r_Theta += 0.5;
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
			else if ((r_Theta < 30) && (dieSwitch != 1)) {
				dieSwitch = 1;
				timeAtFired = time.getElapsedTime().asMilliseconds();
				rSprite = new sf::Sprite();
				rSprite->setTexture(*rExplosionTextures[frame]);
			}
			deltaTime = time.getElapsedTime().asMilliseconds() - timeAtFired;
			actualLocation->x = rPosition->x + (((r_CurrentRadius + r_PosOnRadius) * r_Theta) * cos(r_Theta));
			actualLocation->y = rPosition->y + (((r_CurrentRadius + r_PosOnRadius) * r_Theta) * sin(r_Theta));
			rSprite->setPosition(*actualLocation);
			rSprite->setRotation((r_Theta * r_Theta) + 90);
		}
		else {
			rSprite->setRotation(180);
			rPosition->y += rVelocity->y;
			rSprite->setPosition(*rPosition);
		}
	}
	//Animate();
	//rSprite->setRotation(r_Theta);
}

void Rocket::Animate()
{
	if (timeAtFired + 80 < time.getElapsedTime().asMilliseconds()) {
		timeAtFired = time.getElapsedTime().asMilliseconds();
		//rAlive = false;
		if (frame < 6) {
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

bool Rocket::getAlive()
{
	return rAlive;
}
