#include "GameManager.h"
#include "../systems/Collisions.h"

#include <SFML/Graphics.hpp>
#include "../objects/GameObject.h"
#include "../objects/MovingObject.h"
#include "../engine/events/EventsManager.h"
#include "../objects/Enemy.h"
#include "../objects/Tower.h"
#include "../objects/Background.h"

#include "../engine/rendering/Window.h"

void GameManager::InitBrickBreaker() 
{
    GameManager::spawnGameObject(new Background(700.f, 500.f)); 
    GameManager::spawnGameObject(new Tower(400.f, 300.f, 50.f, 150.f)); 
    GameManager::spawnStaticBody(new Enemy(-30.f, 230.f, 50.f, 50.f));
    GameManager::spawnStaticBody(new Enemy(-90.f, 230.f, 50.f, 50.f));
    GameManager::spawnStaticBody(new Enemy(-150.f, 230.f, 50.f, 50.f));
    GameManager::spawnStaticBody(new Enemy(-210.f, 230.f, 50.f, 50.f));
}

void GameManager::render()
{
    GameManager::window->clearWindow();
    for (int i = 0; i < GameManager::gameObjects.size(); i++)
    {
        GameManager::window->drawOnWindow(gameObjects[i]->getDrawable());
    }
    GameManager::window->display();
}

void GameManager::update()
{
    GameManager::updateDeltaTime();
    GameManager::eventManager.handleSFMLEvents();

    //CALL GAME OBJECTS UPDATE SCRIPTS
    for (int i = 0; i < GameManager::gameObjects.size(); i++)
    {
        gameObjects[i]->update(deltaTime);
    }

    //CALL SYSTEMS
    GameManager::collisions.checkCollisions(); 

    GameManager::deleteGameObjectsAtEndOfUpdate();
}

void GameManager::updateDeltaTime() {
    GameManager::deltaTime = GameManager::clock.getElapsedTime().asSeconds();
    GameManager::clock.restart();
}

void GameManager::spawnGameObject(GameObject* gameObject)
{
    GameManager::gameObjects.push_back(gameObject);
}

void GameManager::killGameObject(GameObject* gameObject)
{
    GameManager::gameObjects.erase(std::remove(GameManager::gameObjects.begin(), GameManager::gameObjects.end(), gameObject), GameManager::gameObjects.end());
    GameManager::collisions.unregisterStaticBody(gameObject);
    GameManager::collisions.unregisterRigidBody((MovingObject*)gameObject);
    GameManager::gameObjectsToDelete.push_back(gameObject);
}

void GameManager::killEnemy(Enemy* enemy)
{
    GameManager::enemies.erase(std::remove(GameManager::enemies.begin(), GameManager::enemies.end(), enemy), GameManager::enemies.end());
}

void GameManager::deleteGameObjectsAtEndOfUpdate() {
    for (GameObject* gameObject : GameManager::gameObjectsToDelete) {
        GameManager::gameObjectsToDelete.erase(std::remove(GameManager::gameObjectsToDelete.begin(), GameManager::gameObjectsToDelete.end(), gameObject), GameManager::gameObjectsToDelete.end());
        delete gameObject;
    }
}

void GameManager::spawnStaticBody(GameObject* staticBody)
{
    GameManager::spawnGameObject(staticBody);
    GameManager::collisions.registerStaticBody(staticBody);
}

void GameManager::spawnRigidBody(MovingObject* rigidBody)
{
    GameManager::spawnGameObject(rigidBody);
    GameManager::collisions.registerRigidBody(rigidBody);
}

void GameManager::registerStaticBody(GameObject* staticBody)
{
    GameManager::collisions.registerStaticBody(staticBody);
}

void GameManager::registerRigidBody(MovingObject* rigidBody) {
    GameManager::collisions.registerRigidBody(rigidBody);
}

void GameManager::bindWindow(Window* window)
{
    GameManager::window = window;
}

Window* GameManager::getWindow()
{
    return GameManager::window;
}

void GameManager::setEnemy(Enemy* enemy)
{
    GameManager::enemies.push_back(enemy);
}

Enemy* GameManager::getTarget()
{
    if (GameManager::enemies.size() == 0)
        return nullptr;

    return *GameManager::enemies.begin();
}

sf::Vector2i GameManager::getMousePosition()
{
    sf::Vector2i mousePosition = GameManager::mouse->getPosition(*GameManager::window->getSFMLObject());
    return mousePosition;
}


std::vector<GameObject*> GameManager::gameObjects;
std::vector<GameObject*> GameManager::gameObjectsToDelete;
std::vector<Enemy*> GameManager::enemies;
Window* GameManager::window;
sf::Mouse* GameManager::mouse;
Collisions GameManager::collisions;
EventsManager GameManager::eventManager;
sf::Clock GameManager::clock;
float GameManager::deltaTime;