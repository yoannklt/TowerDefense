#include "GameObject.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

GameObject::GameObject(float x, float y, float width, float height)
{
	this->position.x = x;
	this->position.y = y;
	this->size.x = width;
	this->size.y = height;
}

GameObject::~GameObject()
{
	// std::cout << "GameObject Destroyed" << std::endl;
}

void GameObject::setPosition(float xpos, float ypos)
{
	this->position.x = xpos;
	this->position.y = ypos;
	this->transformable->setPosition(xpos, xpos);
}

sf::Vector2f GameObject::getPosition() {
	return this->position;
}

float GameObject::getX() {
	return this->position.x;
}

float GameObject::getY() {
	return this->position.y;
}

float GameObject::getXMax() {
	return this->position.x + this->size.x;
}

float GameObject::getYMax() {
	return this->position.y + this->size.y;
}

float GameObject::getWidth() {
	return this->size.x;
}
/*
float GameObject::getHeight() {
	return this->size.y;
}
*/

float GameObject::convertRadiansToDegrees(float radianAngle)
{
	float degreeAngle = radianAngle * 180 / 3.14;
	return degreeAngle;
}