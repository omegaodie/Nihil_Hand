#include "CollisionManager.h"


CollisionManager::CollisionManager(){

}

void CollisionManager::Init(){

}

bool CollisionManager::HitDetectionEnemyPlayer(sf::Vector2f *o1, sf::Vector2f *o2, sf::Vector2f *d1, sf::Vector2f *d2){
	if (o1->x + d1->x > o2->x && o1->x > o2->x + d2->x){
		if (o1->y + d1->y > o2->y && o1->y > o2->y + d2->y){
			return true;
		}
	}
	return false;
}