#include "Text.h"
#include <SFML/Graphics.hpp>

Text::Text(const char* text, sf::Vector2f position, const char* font, int size, sf::Color color) : GameObject(position.x, position.y, size, size)
{
	this->font = new sf::Font();
	this->font->loadFromFile(font);

	this->string = new sf::String(text);
	this->text = new sf::Text(*this->string, *this->font, (unsigned int)size);

	this->drawable = this->text;
	this->transformable = this->text;

	this->text->setPosition(position);
	this->text->setFillColor(color);

}

Text::~Text()
{
	delete this->font;
	delete this->string;
	delete this->text;
}

void Text::updateText(std::string text)
{
	this->string = new sf::String(text);
	this->text->setString(*this->string);
}

void Text::setTextStyle(std::vector<sf::Text::Style> styles)
{
	for (int i = 0; i < styles.size(); i++)
		this->text->setStyle(styles[i]);
}