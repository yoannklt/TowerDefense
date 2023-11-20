#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "../core/GameManager.h"
#include "../engine/rendering/Window.h"
#include "../engine/events/EventsManager.h"

Bullet::Bullet(float x, float y, float diameter, float orientationX, float orientationY) : MovingObject(x, y, diameter, diameter, orientationX, orientationY)
{
	this->shape = new sf::CircleShape(diameter / 2);
	this->drawable = this->shape;
	this->transformable = this->shape;
	this->transformable->setOrigin(diameter / 2, diameter / 2);
	this->setPosition(x - this->transformable->getOrigin().x, y - this->transformable->getOrigin().y);
}

Bullet::Bullet(float x, float y, float radius, float orientationX, float orientationY, sf::Color color) : Bullet(x, y, radius, orientationX, orientationY)
{
	this->shape->setFillColor(color);
}

Bullet::~Bullet()
{
	// std::cout << "Bullet Destroyed" << std::endl;
	GameManager::eventManager.trigger(BULLET_DESTROYED);
	delete this->shape;
}

void Bullet::bounce(int side)
{
	float orientationTab[2] = { orientation.x, orientation.y };
	orientationTab[side] = -orientationTab[side];
	this->orientation.x = orientationTab[0];
	this->orientation.y = orientationTab[1];
}

void Bullet::update(float deltaTime)
{

	if (position.x + size.x >= GameManager::getWindow()->getSFMLObject()->getSize().x or position.x <= 0)
	{
		orientation.x = -orientation.x;
	}

	if (position.y <= 0)
	{
		this->setPosition(position.x, 0);
		orientation.y = -orientation.y;
	}

	MovingObject::update(deltaTime);

	if (position.y >= GameManager::getWindow()->getSFMLObject()->getSize().y) {
		GameManager::killGameObject(this);
	}

}

void Bullet::onCollision(sf::Vector2f collisionSide) {
	this->bounce(collisionSide.x);
}