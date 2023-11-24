#pragma once
#include "GameObject.h"

namespace sf
{
	class Sprite;
}

class Background : public GameObject
{
public:
	Background(float width, float height);
	~Background() { delete this->sprite; };

private:
	sf::Sprite* sprite;
};