#pragma once
#include "GameState.h"

class Window;
class GameObject;
class MovingObject;
class Collisions;

class PlayGameState : public GameState 
{
public:
	PlayGameState();
	~PlayGameState();
	void update(float deltaTime) override;
	void spawnStaticBody(GameObject* staticBody);
	void spawnRigidBody(MovingObject* rigidBody);
	void registerStaticBody(GameObject* staticBody);
	void registerRigidBody(MovingObject* rigidBody);
private:
	Collisions* collisions;
};