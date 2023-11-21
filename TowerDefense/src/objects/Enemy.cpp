#include "Enemy.h"
#include "../engine/textures/TextureManager.h"
#include "../core/GameManager.h"
#include <SFML/Graphics/Sprite.hpp>

Enemy::Enemy(float x, float y, float width, float height, float orientationX, float orientationY) : MovingObject(x, y, height, width, orientationX, orientationY)
{
	GameManager::setEnemy(this);

	this->sprite = new sf::Sprite(*TextureManager::getTexture("enemy.png"));
	this->sprite->setScale(this->size.x / this->sprite->getGlobalBounds().width, this->size.y / this->sprite->getGlobalBounds().height);
	this->drawable = this->sprite;
	this->transformable = this->sprite;
}

void Enemy::update(float deltaTime)
{
	MovingObject::update(deltaTime);
}
