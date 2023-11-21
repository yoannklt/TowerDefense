#include "Tower.h"
#include "Bullet.h"
#include "../core/GameManager.h"
#include "../engine/events/EventsManager.h"
#include "../engine/events/EventsNames.h"
#include "../engine/textures/TextureManager.h"

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../utils/Maths.h"



Tower::Tower(float x, float y, float width, float height) : GameObject(x, y, width, height)
{
	this->sprite = new sf::Sprite(*TextureManager::getTexture("tower.png"));
	this->drawable = this->sprite;
	this->transformable = this->sprite;
	this->sprite->setPosition(x, y);
	this->sprite->setScale(this->size.x / this->sprite->getGlobalBounds().width, this->size.y / this->sprite->getGlobalBounds().height);
	this->sprite->setOrigin(width, height);

}

Tower::~Tower()
{
	// std::cout << "Canon Destroyed" << std::endl;
	delete this->sprite;
}

void Tower::update(float deltaTime)
{
	sf::Vector2i mousePosition = GameManager::getMousePosition();

	//std::cout << "Mouse X: " << mousePosition.x << std::endl << "Mouse Y: " << mousePosition.y << std::endl;

	float xPoint = std::abs(position.x);
	float yPoint = std::abs(position.y);

	float radianAngle = atan2f(xPoint - mousePosition.x, yPoint - mousePosition.y);
	float degreeAngle = convertRadiansToDegrees(radianAngle);

	this->orientation.x = xPoint - mousePosition.x;
	this->orientation.y = yPoint - mousePosition.y;

	this->sprite->setRotation(-degreeAngle);
}