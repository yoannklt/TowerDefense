#pragma once

#include "MovingObject.h"

namespace sf
{
	class Color;
	class CircleShape;
}


class Projectile : public MovingObject
{
public:
	Projectile(float x, float y, float radius, float orientationX, float orientationY);
	Projectile(float x, float y, float radius, float orientationX, float orientationY, sf::Color color);
	~Projectile() override;

	void update(float deltaTime) override;
	void onCollision(sf::Vector2f collisionSide) override;
	void bounce(int side);

protected:
	sf::CircleShape* shape;

private:
};