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
	if (cooldown > 0)
	{
		cooldown -= deltaTime;
		return;
	}
	cooldown = defaultCooldown;

	Enemy* target = GameManager::getTarget();

	if (target == nullptr)
	{
		std::cout << "plus d'ennemi" << std::endl;
		return;

	}

	sf::Vector2f targetPosition = target->getPosition();

	float xPoint = std::abs(position.x);
	float yPoint = std::abs(position.y);

	float radianAngle = atan2f(xPoint - targetPosition.x, yPoint - targetPosition.y);
	float degreeAngle = convertRadiansToDegrees(radianAngle);

	this->orientation.x = xPoint - targetPosition.x;
	this->orientation.y = yPoint - targetPosition.y;

	shoot();

}

void Tower::shoot()
{
	GameManager::spawnRigidBody(new Bullet(position.x, position.y, 15, -orientation.x, -orientation.y, sf::Color::White));
}
