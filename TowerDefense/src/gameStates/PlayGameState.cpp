#include "PlayGameState.h"
#include "../systems/Collisions.h"
#include "../objects/MovingObject.h"
#include <iostream>
#include "../objects/Tower.h"

PlayGameState::PlayGameState()
{
    this->gameObjects.push_back(new Tower(100,40,50,200));
    this->collisions = new Collisions();
}

PlayGameState::~PlayGameState()
{
}

void PlayGameState::update(float deltaTime) {
    GameState::update(deltaTime);
    this->collisions->checkCollisions();
}

void PlayGameState::spawnStaticBody(GameObject* staticBody)
{
    this->spawnGameObject(staticBody);
    this->collisions->registerStaticBody(staticBody);
}

void PlayGameState::spawnRigidBody(MovingObject* rigidBody)
{
    this->spawnGameObject(rigidBody);
    this->collisions->registerRigidBody(rigidBody);
}

void PlayGameState::registerStaticBody(GameObject* staticBody)
{
    this->collisions->registerStaticBody(staticBody);
}

void PlayGameState::registerRigidBody(MovingObject* rigidBody) {
    this->collisions->registerRigidBody(rigidBody);
}
