#include "Experience.h"
#include "SFML/Graphics.hpp"
#include "../core/GameManager.h"
#include "../engine/events/EventsManager.h"

Experience::Experience(const char* text, sf::Vector2f position, const char* font, int size, sf::Color color) : Text(text, position, font, size, color)
{
	GameManager::eventManager.subscribe<Experience>(ENEMY_KILL, this, &Experience::incrementExperienceOnEnemyKilled);
}

Experience::~Experience()
{
}

int Experience::incrementExperienceOnEnemyKilled()
{
	this->experience += 50;
	switch (this->experience)
	{
	case 100:
		incrementLevel();
		break;

	case 250:
		incrementLevel();
		break;
	
	case 450:
		incrementLevel();
		break;

	case 700:
		incrementLevel();
		break;

	default:
		break;
	}

	return 0;
}

int Experience::incrementLevel()
{
	this->level += 1;
	this->updateText("Level: " + std::to_string(this->level));

	return 0;
}
