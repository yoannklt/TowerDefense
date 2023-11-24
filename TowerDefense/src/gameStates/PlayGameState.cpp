#include "PlayGameState.h"
#include "PauseGameState.h"
#include "GameOverGameState.h"
#include "../systems/Collisions.h"
#include "../objects/MovingObject.h"
#include "../objects/Tower.h"
#include "../objects/Fortress.h"
#include "../objects/Background.h"
#include "../objects/Score.h"
#include "../objects/Experience.h"
#include "../engine/core/GameManager.h"
#include "../engine/events/MethodCommand.h"

PlayGameState::PlayGameState()
{
    this->collisions = new Collisions();
    this->spawnGameObject(new Background(700.f, 500.f));

    this->spawnGameObject(new Score("Golds: 0", { 50, 400 }, "data/assets/graphics/fonts/Roboto-Regular.ttf", 40, sf::Color::White));
    this->spawnGameObject(new Experience("Level: 0", { 400, 400 }, "data/assets/graphics/fonts/Roboto-Regular.ttf", 40, sf::Color::White));

    this->spawnGameObject(new Tower(170.f, 100.f, 50.f, 150.f));
    Text* FortressHealth = new Text("Level: 0", {610.f,  150.f - 40}, "data/assets/graphics/fonts/Roboto-Regular.ttf", 20, sf::Color::White);
    this->spawnGameObject(FortressHealth);
    this->spawnGameObject(new Fortress(630.f, 150.f, 150.f, 150.f, FortressHealth));
    this->enemiesAmountToSpawn = 4;

    //should be wrapped into stateEnter() method
    this->enter();
}

PlayGameState::~PlayGameState()
{
}

void PlayGameState::switchStateDefeat() {
    //should be wrapped into stateExit() method
    GameManager::instance().getEventsManager()->unsubscribe(GAME_OVER_DEFEAT, new MethodCommand<PlayGameState>(this, &PlayGameState::switchStateDefeat));
    GameManager::instance().getEventsManager()->unsubscribe(KEY_ESCAPE_PRESSED, new MethodCommand<PlayGameState>(this, &PlayGameState::switchStatePause));
	GameManager::instance().switchGameState(new GameOverGameState(true, this));
}

void PlayGameState::switchStatePause() {
    GameManager::instance().getEventsManager()->unsubscribe(GAME_OVER_DEFEAT, new MethodCommand<PlayGameState>(this, &PlayGameState::switchStateDefeat));
    GameManager::instance().getEventsManager()->unsubscribe(KEY_ESCAPE_PRESSED, new MethodCommand<PlayGameState>(this, &PlayGameState::switchStatePause));
    GameManager::instance().switchGameState(new PauseGameState(this));
}

void PlayGameState::update(float deltaTime) {
    this->timeBetweenSpawn -= deltaTime;

    if (this->timeBetweenSpawn <= 0 && this->enemiesAmountToSpawn > 0)
    {
        this->spawnEnemy(new Enemy(-40.f, 230.f, 50.f, 50.f));
        this->enemiesAmountToSpawn -= 1;
        this->timeBetweenSpawn = 1.5f;
    }

    GameState::update(deltaTime);
    this->collisions->checkCollisions();
}

void PlayGameState::enter()
{
    GameManager::instance().getEventsManager()->subscribe(GAME_OVER_DEFEAT, new MethodCommand<PlayGameState>(this, &PlayGameState::switchStateDefeat));
    GameManager::instance().getEventsManager()->subscribe(KEY_ESCAPE_PRESSED, new MethodCommand<PlayGameState>(this, &PlayGameState::switchStatePause));
}

void PlayGameState::killGameObject(GameObject* gameObject)
{
	GameState::killGameObject(gameObject);
    this->enemies.erase(std::remove(this->enemies.begin(), this->enemies.end(), gameObject), this->enemies.end());
	this->collisions->unregisterStaticBody(gameObject);
	this->collisions->unregisterRigidBody((MovingObject*) gameObject);
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

void PlayGameState::spawnEnemy(Enemy* enemy)
{
    this->enemies.push_back(enemy);
    this->spawnGameObject(enemy);
    this->collisions->registerStaticBody(enemy);
}

Enemy* PlayGameState::getEnemies()
{
    if (this->enemies.size() == 0)
        return nullptr;
    return *this->enemies.begin();
}