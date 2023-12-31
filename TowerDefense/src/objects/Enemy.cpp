#include "Enemy.h"
#include "../engine/textures/TextureManager.h"
#include "../core/GameManager.h"
#include "../engine/events/EventsManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include "../utils/Maths.h"
#include "Tower.h"

Enemy::Enemy(float x, float y, float width, float height) : GameObject(x, y, height, width)
{
	GameManager::setEnemy(this);

	this->sprite = new sf::Sprite(*TextureManager::getTexture("enemy.png"));
	this->sprite->setScale(width / this->sprite->getGlobalBounds().width, height / this->sprite->getGlobalBounds().height);
	this->sprite->setOrigin(width/2, height);

	this->sprite->setPosition(x, y);

	this->drawable = this->sprite;
	this->transformable = this->sprite;

	this->checkPoints.push_back({ 105, 230 });
	this->checkPoints.push_back({ 105, 85 });
	this->checkPoints.push_back({ 240, 85 });
	this->checkPoints.push_back({ 240, 290 });
	this->checkPoints.push_back({ 430, 290 });
	this->checkPoints.push_back({ 430, 190 });
	this->checkPoints.push_back({ 740, 190 });

}

Enemy::~Enemy() 
{
	delete this->sprite; 
};

void Enemy::update(float deltaTime)
{

	if (checkPointIndex == this->checkPoints.size())
		return;

	sf::Vector2f distance = {
		checkPoints[checkPointIndex].x - this->position.x,
		checkPoints[checkPointIndex].y - this->position.y
	};

	if (Maths::getNorm(distance) > 5.f)
	{
		this->orientation.x = this->checkPoints[checkPointIndex].x - this->position.x; 
		this->orientation.y = this->checkPoints[checkPointIndex].y - this->position.y; 
		this->orientation = Maths::normalize(orientation); 

		this->position.x += orientation.x * deltaTime * speed; 
		this->position.y += orientation.y * deltaTime * speed; 
		this->sprite->setPosition(this->position.x, this->position.y);
	}
	else
		this->checkPointIndex++;
	 
}

void Enemy::onCollision(sf::Vector2f collisionSide)
{
	this->health -= 1;
	this->speed -= this->speed * 25 / 100;
	if (this->health == 0)
	{
		GameManager::eventManager.trigger(ENEMY_KILL); 
		GameManager::killGameObject(this);
		GameManager::killEnemy(this);
	}
}



