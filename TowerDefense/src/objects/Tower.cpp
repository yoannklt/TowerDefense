#include "Tower.h"
#include "Projectile.h"
#include "../engine/core/GameManager.h"
#include "../engine/core/GameState.h"
#include "../gameStates/PlayGameState.h"
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
	cooldown -= deltaTime;
	if (cooldown > 0)
		return;
	cooldown = defaultCooldown;

	Enemy* target = ((PlayGameState*)GameManager::instance().getGameState())->getEnemies();

	if (target == nullptr)
		return;

	sf::Vector2f targetPosition = target->getPosition();

	float xPoint = std::abs(position.x);
	float yPoint = std::abs(position.y);

	float radianAngle = atan2f(xPoint - targetPosition.x, yPoint - targetPosition.y);
	float degreeAngle = Maths::convertRadiansToDegrees(radianAngle);

	this->orientation.x = xPoint - targetPosition.x;
	this->orientation.y = yPoint - targetPosition.y;

	sf::Vector2f vectorBetweenTargetAndTower = {
		target->getPosition().x - this->position.x,
		target->getPosition().y - this->position.y
	};

	if (Maths::getNorm(vectorBetweenTargetAndTower) <= 250)
	{
		shoot();
	}
}

void Tower::shoot()
{
	((PlayGameState*) GameManager::instance().getGameState())->spawnRigidBody(new Projectile(position.x, position.y, 15, -orientation.x, -orientation.y, sf::Color::Blue));
}