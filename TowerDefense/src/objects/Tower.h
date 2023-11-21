#pragma once

#include <SFML/System/Vector2.hpp>
#include "Enemy.h"

namespace sf
{
	class Color;
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

protected:
	sf::Sprite* sprite;

private:
	bool canShoot = true;
};

