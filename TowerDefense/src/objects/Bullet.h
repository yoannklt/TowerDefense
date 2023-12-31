#pragma once

#include "MovingObject.h"

namespace sf
{
	class Color;
	class CircleShape;
}


class Bullet : public MovingObject
{
public:
	Bullet(float x, float y, float radius, float orientationX, float orientationY);
	Bullet(float x, float y, float radius, float orientationX, float orientationY, sf::Color color);
	~Bullet() override;

	void update(float deltaTime) override;
	void onCollision(sf::Vector2f collisionSide) override;
	void bounce(int side);

protected:
	sf::CircleShape* shape;

private:
};