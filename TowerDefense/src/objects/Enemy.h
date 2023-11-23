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
	~Enemy();

	void update(float deltaTime) override;

	void onCollision(sf::Vector2f collisionSide) override;

private:
	sf::Sprite* sprite;
	std::vector<sf::Vector2f> checkPoints;

	int health = 3;
	int maxHealth = health;
	int checkPointIndex = 0;
	int speed = 100;

	sf::Vector2f orientation = { 0, 0 };
};

