#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include "../events/EventsManager.h"
//class EventsManager;
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
	GameState* getGameState();
	void switchGameState(GameState*);


	EventsManager* getEventsManager();
	Window* getWindow();

private:
	GameManager() {};
	static GameManager* instance_;

	GameState* gameState;
	void updateDeltaTime();
	sf::Clock* clock = new sf::Clock();
	float deltaTime = 0;
	Window* window;
	
	EventsManager* eventsManager = new EventsManager();
	
};