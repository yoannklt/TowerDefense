#pragma once

#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics/Text.hpp"
#include "../objects/GameObject.h"
#include <string>

namespace sf
{
	class Font;
	class String;
	class Color;
}

class Text : public GameObject
{
public:
	Text(const char* text, sf::Vector2f position, const char* font, int size, sf::Color color);
	~Text();

	void updateText(std::string text);
	void setTextStyle(std::vector<sf::Text::Style> styles);
	inline sf::Text* getText() { return text; }

protected:
	sf::Font* font;
	sf::String* string;
	sf::Text* text;
};

