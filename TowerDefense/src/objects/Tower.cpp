#include "Tower.h"
#include "Bullet.h"
#include "../core/GameManager.h"
#include "../engine/events/EventsManager.h"
#include "../engine/events/EventsNames.h"

#include <cmath>
#include <SFML/Graphics.hpp>

#include "../utils/Maths.h"



Tower::Tower(float x, float y, float width, float height) : GameObject(x, y, width, height)
{
	this->shape = new sf::RectangleShape(sf::Vector2f(width, height));
	this->drawable = this->shape;
	this->transformable = this->shape;

	this->shape->setPosition(x, y);
	this->shape->setOrigin(width / 2, height);

	GameManager::eventManager.subscribe<Tower>(MOUSE_LEFT_PRESSED, this, &Tower::launchBall);
	GameManager::eventManager.subscribe<Tower>(BULLET_DESTROYED, this, &Tower::toggleShootCondition);
	//GameManager::spawnGameObject(new Ball(x, y, width, orientation.x, orientation.y, sf::Color::Cyan));
}

Tower::Tower(float x, float y, float width, float height, sf::Color color) : Tower(x, y, width, height)
{
	this->shape->setFillColor(color);
	this->shape->setOutlineThickness(10.f);
	this->shape->setOutlineColor(sf::Color::Cyan);

}

Tower::~Tower()
{
	// std::cout << "Canon Destroyed" << std::endl;
	delete this->shape;
}

void Tower::update(float deltaTime)
{
	sf::Vector2i mousePosition = GameManager::getMousePosition();

	float xPoint = std::abs(position.x);
	float yPoint = std::abs(position.y);

	float radianAngle = atan2f(xPoint - mousePosition.x, yPoint - mousePosition.y);
	float degreeAngle = convertRadiansToDegrees(radianAngle);

	this->orientation.x = xPoint - mousePosition.x;
	this->orientation.y = yPoint - mousePosition.y;

	if (degreeAngle < 90 and degreeAngle > -90)
	{
		this->shape->setRotation(-degreeAngle);
	}
}

int Tower::launchBall()
{
	if (canShoot)
	{
		this->canShoot = !this->canShoot;
		sf::Vector2f normalizeOrientation = Maths::normalize(this->orientation);
		GameManager::spawnRigidBody(new Bullet(
			this->shape->getPosition().x - normalizeOrientation.x * size.y,
			this->shape->getPosition().y - normalizeOrientation.y * size.y,
			30.f,
			-normalizeOrientation.x,
			-normalizeOrientation.y, sf::Color::Magenta));
	}
	return 0;
}