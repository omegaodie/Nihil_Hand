#ifndef __COLLISIONMANAGER_H__
#define ___COLLISIONMANAGER_H__


#include <SFML/Graphics.hpp>
#include "Bullet.h"



class CollisionManager
{
public:


	CollisionManager::CollisionManager();

	CollisionManager::~CollisionManager();

	void CollisionManager::Init();


	bool CollisionManager::HitDetectionEnemyPlayer(sf::Vector2f *o1, sf::Vector2f *o2, sf::Vector2f *d1, sf::Vector2f *d2);

};

#endif 