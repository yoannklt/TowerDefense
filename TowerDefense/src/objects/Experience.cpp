#include "Experience.h"
#include "SFML/Graphics.hpp"
#include "../engine/core/GameManager.h"
#include "../engine/events/EventsManager.h"
#include "../engine/events/MethodCommand.h"

Experience::Experience(const char* text, sf::Vector2f position, const char* font, int size, sf::Color color) : Text(text, position, font, size, color)
{
	GameManager::instance().getEventsManager()->subscribe(ENEMY_KILLED, new MethodCommand<Experience>(this, &Experience::incrementExperienceOnEnemyKilled));
}

Experience::~Experience()
{
}

void Experience::incrementExperienceOnEnemyKilled()
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
}

int Experience::incrementLevel()
{
	this->level += 1;
	this->updateText("Level: " + std::to_string(this->level));

	return 0;
}