#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
#include <vector>


namespace sf
{
	class Sprite;
}

class Ball;

class Tower : public GameObject
{
public:
	// CONSTRUCTORS / DESTRUCTORS
	Tower(float x, float y, float width, float height);
	~Tower();

	void update(float deltaTime) override;

private:
	void shoot();

	float defaultCooldown = 3;
	float cooldown = 3;

	sf::Sprite* sprite;
};