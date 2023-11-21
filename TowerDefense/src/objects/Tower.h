#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
#include "Enemy.h"
#include <vector>


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
	std::vector<Enemy*> enemies;
};

