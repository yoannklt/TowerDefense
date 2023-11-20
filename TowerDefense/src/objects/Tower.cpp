#include "Tower.h"
#include "Bullet.h"
#include "../core/GameManager.h"
#include "../engine/events/EventsManager.h"
#include "../engine/events/EventsNames.h"
#include "../engine/textures/TextureManager.h"

#include <cmath>
#include <SFML/Graphics.hpp>

#include "../utils/Maths.h"



Tower::Tower(float x, float y, float width, float height) : GameObject(x, y, width, height)
{
	this->sprite = new sf::Sprite(*TextureManager::getTexture("tower.png"));
	this->drawable = this->sprite;
	this->transformable = this->sprite;
	//this->sprite->setOrigin

	GameManager::eventManager.subscribe<Tower>(MOUSE_LEFT_PRESSED, this, &Tower::launchBall);
	GameManager::eventManager.subscribe<Tower>(BULLET_DESTROYED, this, &Tower::toggleShootCondition);
}

Tower::~Tower()
{
	// std::cout << "Canon Destroyed" << std::endl;
	delete this->sprite;
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
		this->sprite->setRotation(-degreeAngle);
	}
}

int Tower::launchBall()
{
	if (canShoot)
	{
		this->canShoot = !this->canShoot;
		sf::Vector2f normalizeOrientation = Maths::normalize(this->orientation);
		GameManager::spawnRigidBody(new Bullet(
			this->sprite->getPosition().x - normalizeOrientation.x * size.y,
			this->sprite->getPosition().y - normalizeOrientation.y * size.y,
			30.f,
			-normalizeOrientation.x,
			-normalizeOrientation.y, sf::Color::Magenta));
	}
	return 0;
}