#include "Explosion.h"


Explosion::Explosion(const GameData &gdata) : gd(gdata){
	setExplode = false;
}

void Explosion::Init(sf::Vector2f vec){
	setExplode = true;
	position = sf::Vector2f(vec);
	explSprite = sf::Sprite();
	currentExplodeFrame = 0;
	C = sf::Clock();
	explSprite.setPosition(position);
	explSprite.setOrigin(sf::Vector2f(50, 50));
}


void Explosion::Explode(sf::RenderWindow &w){
	if (setExplode == true){
		//if (explosionTimer + 100 < C.getElapsedTime().asMilliseconds()){
			if (currentExplodeFrame < 81){
				explSprite.setTexture(*(gd.m_RocketAnimTextures[currentExplodeFrame]));
				w.draw(explSprite);
				currentExplodeFrame++;
			}
			else{
				setExplode = false;
				currentExplodeFrame = 0;
			}
		//}
	}
}


bool Explosion::getActive(){
	return setExplode;
}