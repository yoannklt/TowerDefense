#pragma once
#include "Text.h"

namespace sf
{
	class Color;
}

class Experience : public Text
{
public:
	Experience(const char* text, sf::Vector2f position, const char* font, int size, sf::Color color);
	int incrementExperienceOnEnemyKilled();
	int incrementLevel();
	~Experience();

private:
	int experience = 0;
	int level = 0;
};

