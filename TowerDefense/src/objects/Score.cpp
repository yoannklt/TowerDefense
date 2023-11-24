#include "Score.h"
#include "../engine/core/GameManager.h"
#include "../engine/events/EventsManager.h"
#include "../engine/events/MethodCommand.h"
#include <iostream>

Score::Score(const char* text, sf::Vector2f position, const char* font, int size, sf::Color color) : Text(text, position, font, size, color)
{
	GameManager::instance().getEventsManager()->subscribe(ENEMY_KILLED, new MethodCommand<Score>(this, &Score::incrementScoreOnEnemyKilled));

}

void Score::incrementScoreOnEnemyKilled()
{
	this->score += 40;
	this->updateText("Golds: " + std::to_string(this->score));
}