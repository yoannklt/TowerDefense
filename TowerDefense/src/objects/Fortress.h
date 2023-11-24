#pragma once
#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
#include "Enemy.h"
#include <vector>
#include "Text.h"


namespace sf
{
	class Sprite;
}

class Fortress : public GameObject
{
public:
	// CONSTRUCTORS / DESTRUCTORS
	Fortress(float x, float y, float width, float height, Text* text);
	~Fortress();

	void update(float deltaTime) override;

	void onDamaged();

private:

	Text* healthText;
	int health = 3;
	sf::Sprite* sprite;

};