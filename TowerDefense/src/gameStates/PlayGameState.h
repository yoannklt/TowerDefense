#pragma once
#include "../engine/core/GameState.h"

class Window;
class GameObject;
class MovingObject;
class Collisions;
class Enemy;

class PlayGameState : public GameState 
{
public:
	PlayGameState();
	~PlayGameState();
	void switchStateDefeat();
	void switchStatePause();
	void enter() override;
	void update(float deltaTime) override;
	void spawnStaticBody(GameObject* staticBody);
	void spawnRigidBody(MovingObject* rigidBody);
	void registerStaticBody(GameObject* staticBody);
	void registerRigidBody(MovingObject* rigidBody);
	void killGameObject(GameObject* gameObject) override;
	void spawnEnemy(Enemy* enemy);
	Enemy* getEnemies();
private:
	Collisions* collisions;
	std::vector<Enemy*> enemies;
	int enemiesAmountToSpawn;
	float timeBetweenSpawn;
};