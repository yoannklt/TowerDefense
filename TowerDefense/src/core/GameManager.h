#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

class EventsManager;
class Window;
class GameState;

class GameManager
{
public:
	~GameManager() {};
	static GameManager& instance();
	void InitGameManager(GameState* initialGameState);
	void render();
	void update();
	Window* getWindow();
	GameState* getGameState();
	void switchGameState(GameState*);
	EventsManager* getEventsManager();
	//GameManager(const GameManager& obj) = delete;

private:
	void updateDeltaTime();
	GameManager() {};

	sf::Clock* clock = new sf::Clock();
	float deltaTime = 0;
	Window* window;
	GameState* gameState;
	EventsManager* eventsManager;
	static GameManager* instance_;
};