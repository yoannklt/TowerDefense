#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameObject.h"

namespace sf
{
	class Color;
	class RectangleShape;
}

class Ball;

class Tower : public GameObject
{
public:
	// CONSTRUCTORS / DESTRUCTORS
	Tower(float x, float y, float width, float height);
	Tower(float x, float y, float width, float height, sf::Color color);
	~Tower();

	void update(float deltaTime) override;

	// TEST FUNCTIONS
	int launchBall();
	inline int toggleShootCondition() { this->canShoot = !this->canShoot; return 0; };

protected:
	sf::RectangleShape* shape;

private:
	bool canShoot = true;
};

