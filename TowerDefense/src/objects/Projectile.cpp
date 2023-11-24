#include "Projectile.h"
#include <SFML/Graphics.hpp>
#include "../engine/core/GameManager.h"
#include "../engine/core/GameState.h"
#include "../engine/rendering/Window.h"
#include "../engine/events/EventsManager.h"
#include <iostream>

Projectile::Projectile(float x, float y, float diameter, float orientationX, float orientationY) : MovingObject(x, y, diameter, diameter, orientationX, orientationY)
{
	this->shape = new sf::CircleShape(diameter / 2);
	this->drawable = this->shape;
	this->transformable = this->shape;
	this->transformable->setOrigin(diameter / 2, diameter / 2);
	this->setPosition(x - this->transformable->getOrigin().x, y - this->transformable->getOrigin().y);
}

Projectile::Projectile(float x, float y, float radius, float orientationX, float orientationY, sf::Color color) : Projectile(x, y, radius, orientationX, orientationY)
{
	this->shape->setFillColor(color);
	this->shape->setOutlineColor(sf::Color::Cyan);
	this->shape->setOutlineThickness(2.5f);
}

Projectile::~Projectile()
{
	// std::cout << "Bullet Destroyed" << std::endl;
	GameManager::instance().getEventsManager()->trigger(BULLET_DESTROYED);
	delete this->shape;
}

void Projectile::bounce(int side)
{
	float orientationTab[2] = { orientation.x, orientation.y };
	orientationTab[side] = -orientationTab[side];
	this->orientation.x = orientationTab[0];
	this->orientation.y = orientationTab[1];
}

void Projectile::update(float deltaTime)
{

	MovingObject::update(deltaTime);

	sf::Vector2u windowSize =
	{
		GameManager::instance().getWindow()->getSFMLObject()->getSize().x,
		GameManager::instance().getWindow()->getSFMLObject()->getSize().y
	};

	if ((this->position.x > windowSize.x || this->position.x < 0) || (this->position.y > windowSize.y || this->position.y < 0))
	{
		GameManager::instance().getGameState()->killGameObject(this);
		std::cout << "Destroyed" << std::endl;
	}

}

void Projectile::onCollision(sf::Vector2f collisionSide) {
	this->bounce(collisionSide.x);
	GameManager::instance().getGameState()->killGameObject(this);
}