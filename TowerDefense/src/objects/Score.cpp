#include "Score.h"
#include "../core/GameManager.h"
#include "../engine/events/EventsManager.h"
#include <iostream>

Score::Score(const char* text, sf::Vector2f position, const char* font, int size, sf::Color color) : Text(text, position, font, size, color)
{
	GameManager::eventManager.subscribe<Score>(ENEMY_KILL, this, &Score::incrementScoreOnEnemyKilled);

}

int Score::incrementScoreOnEnemyKilled()
{
	this->score += 40;
	this->updateText("Golds: " + std::to_string(this->score));

	return 0;
}
