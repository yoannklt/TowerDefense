#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <string>

namespace sf
{
	class Mouse;
}

class GameObject;
class MovingObject;
class Collisions;
class EventsManager;
class Window;
class Text;
class Enemy;

class GameManager
{
public:

	//~GameManager();
	static void InitBrickBreaker();
	static void render();
	static void update();
	static void spawnGameObject(GameObject* gameObject);
	static void killGameObject(GameObject* gameObject);
	static void spawnStaticBody(GameObject* staticBody);
	static void spawnRigidBody(MovingObject* rigidBody);
	static void registerStaticBody(GameObject* staticBody);
	static void registerRigidBody(MovingObject* rigidBody);
	static sf::Vector2i getMousePosition();
	static void bindWindow(Window* window);
	static Window* getWindow();
	static void setEnemy(Enemy* enemy);
	static Enemy* getTarget();

	static EventsManager eventManager;



private:
	//GameManager(sf::RenderWindow* window););

	static void deleteGameObjectsAtEndOfUpdate();
	static void updateDeltaTime();

	static std::vector<GameObject*> gameObjects;
	static std::vector<Enemy*> enemies;
	static std::vector<GameObject*> gameObjectsToDelete;

	static Collisions collisions;

	static sf::Clock clock;
	static float deltaTime;
	static float deltaTimeAsSeconds;


	static Window* window;
	static sf::Mouse* mouse;

};