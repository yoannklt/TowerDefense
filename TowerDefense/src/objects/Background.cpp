#include "Background.h"
#include "../engine/textures/TextureManager.h"
#include <SFML/Graphics/Sprite.hpp>

Background::Background(float width, float height) : GameObject(0.f, 0.f, width, height)
{
	this->sprite = new sf::Sprite(*TextureManager::getTexture("background.png"));
	this->transformable = this->sprite;
	this->drawable = this->sprite;
	this->sprite->setScale(this->size.x / this->sprite->getGlobalBounds().width, this->size.y / this->sprite->getGlobalBounds().height);
}