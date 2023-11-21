#pragma once

#include <SFML/System/Vector2.hpp>

namespace sf
{
	class Transformable;
	class Drawable;
}

class GameObject
{
public:
	// CONSTRUCTORS / DESTRUCTORS
	GameObject(float x, float y, float width, float height);
	virtual ~GameObject();
	//
	virtual void update(float deltaTime) {};

	// GETTERS/SETTERS
	virtual void onCollision(sf::Vector2f collisionSide) {};
	sf::Vector2f getPosition();
	void setPosition(float xpos, float ypos);
	inline sf::Vector2f getOrientation() { return orientation; };
	inline void setOrientation(float orientationX, float orientationY) { orientation = { orientationX, orientationY }; };
	float getX();
	float getY();
	float getXMax();
	float getYMax();
	float getWidth();
	inline float getHeight()
	{
		return this->size.y;
	};

	inline sf::Drawable* getDrawable() { return this->drawable; };
	inline sf::Transformable* getTransformable() { return this->transformable; };
	//to move to math namespace
	float convertRadiansToDegrees(float radianAngle);

protected:
	sf::Drawable* drawable;
	sf::Transformable* transformable;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f orientation;
};