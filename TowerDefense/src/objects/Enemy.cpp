#include "Enemy.h"
#include "../engine/textures/TextureManager.h"
#include "../core/GameManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include "Tower.h"

Enemy::Enemy(float x, float y, float width, float height) : GameObject(x, y, height, width)
{
	this->sprite = new sf::Sprite(*TextureManager::getTexture("enemy.png"));
	this->sprite->setScale(width / this->sprite->getGlobalBounds().width, height / this->sprite->getGlobalBounds().height);
	this->sprite->setOrigin(width/2, height);

	//std::cout << this->sprite->getOrigin().x << "   " << this->sprite->getOrigin().y << std::endl;

	this->sprite->setPosition(x, y);

	this->drawable = this->sprite;
	this->transformable = this->sprite;

	//this->checkPoints.push_back({ x, y });
}

void Enemy::update(float deltaTime)
{
	for (int i = 0; i < checkPoints.size(); i++)
	{
		if (i + 1 == this->checkPoints.size())
			break;

		if (position.x != checkPoints[i + 1].x && position.y != checkPoints[i + 1].y)
		{
			this->position.x += (this->checkPoints[i + 1].x - this->position.x);
			this->position.y += (this->checkPoints[i + 1].y - this->position.y);
			this->sprite->setPosition(this->position.x, this->position.y);
		}
		else
			this->checkPointIndex++;
	}

}

void Enemy::onCollision(sf::Vector2f collisionSide)
{
	this->health -= 1;
	if (this->health == 0)
	{
		GameManager::killGameObject(this);
	}
}


