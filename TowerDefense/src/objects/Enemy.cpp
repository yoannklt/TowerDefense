#include "Enemy.h"
#include "../engine/textures/TextureManager.h"
#include "../core/GameManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include "Tower.h"

Enemy::Enemy(float x, float y, float width, float height) : GameObject(x, y, height, width)
{
	this->sprite = new sf::Sprite(*TextureManager::getTexture("enemy.png"));
	this->sprite->setScale(this->size.x / this->sprite->getGlobalBounds().width, this->size.y / this->sprite->getGlobalBounds().height);
	this->drawable = this->sprite;
	this->transformable = this->sprite;

	this->checkPoints.push_back({ x, y });

	x = this->checkPoints.front().x; 
	y = this->checkPoints.front().y; 

	this->checkPoints.push_back({ 50, 50 });
	this->checkPoints.push_back({ 50, 500 });
}

void Enemy::update(float deltaTime)
{
	for (int i = 0; i < checkPoints.size(); i++)
	{
		if (i + 1 == this->checkPoints.size())
			return;

		if (position.x != checkPoints[i + 1].x && position.y != checkPoints[i + 1].y)
		{
			this->position.x += (this->checkPoints[i + 1].x - this->position.x) * deltaTime;
			this->position.y += (this->checkPoints[i + 1].y - this->position.y) * deltaTime;
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


