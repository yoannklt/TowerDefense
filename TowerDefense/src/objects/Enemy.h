#pragma once
#include "MovingObject.h"
#include "SFML/System/Vector2.hpp"
#include <vector>

namespace sf
{
	class Sprite;
	class Vector;
}

class Enemy : public GameObject
{
public:
	Enemy(float x, float y, float width, float height);
	~Enemy() { delete this->sprite; };

	void update(float deltaTime) override;

	void onCollision(sf::Vector2f collisionSide) override;


private:
	sf::Sprite* sprite;
	int health = 2;
	int maxHealth = health;
	std::vector<sf::Vector2f> checkPoints;
	int checkPointIndex = 0;
	int speed = 100;

	sf::Vector2f orientation = { 0, 0 };
};

