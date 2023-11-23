#pragma once
#include "Text.h"

class Score : public Text
{
public:
	Score(const char* text, sf::Vector2f position, const char* font, int size, sf::Color color);
	int incrementScoreOnEnemyKilled();
	~Score() {};

private:
	int score = 0;
};