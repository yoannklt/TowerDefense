#pragma once
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	MovingObject(float x, float y, float width, float height, float orientationX, float orientationY);
	~MovingObject() override {};

	virtual void update(float deltaTime) override;

protected:
	int speed = 500;
};