#pragma once
#include "MovingObject.h"

namespace sf
{
	class Sprite;
}

class Enemy : public MovingObject
{
public:
	Enemy(float x, float y, float width, float height, float orientationX, float orientationY);
	~Enemy() {};

	void update(float deltaTime) override;

private:
	sf::Sprite* sprite;
	int health = 5;
	int maxHealth = health;
};

