#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include "EventsNames.h"
#include "AbstractCommand.h"



class VoidClass {};


typedef enum EventCallbackReturns {
	SUCCESS = 0,
	FAILURE,
	STOP_PROPAGATE,
	EVENT_CALLBACK_RETURNS_AMOUNT
} EventCallbackReturn;

class EventsManager
{
public:
	EventsManager();
	~EventsManager();

	void subscribe(EventName eventName, AbstractCommand* command)
	{
		eventCallbacksMap[eventName].push_back(command);
	}

	void unsubscribe(EventName eventName, AbstractCommand* commandToDelete)
	{
		std::vector<AbstractCommand*>* eventCommands = &eventCallbacksMap[eventName];
		int index = 0;
		for (AbstractCommand* command : *eventCommands) {
			if (commandToDelete->compareCommandsIdentifier(command->commandIdentifier)) {
				eventCommands->erase(eventCommands->begin() + index);
			}
			index++;
		}
	}

	void handleSFMLEvents();
	void trigger(EventName eventName);

	inline EventName getSFMLKeyPressedEventName() { return EventsManager::SFMLKeyPressedTranslationMap[this->event.key.code]; };

	inline EventName getSFMLKeyReleasedEventName() { return EventsManager::SFMLKeyReleasedTranslationMap[this->event.key.code]; };

	inline EventName getSFMLMouseButtonPressedEventName() { return EventsManager::SFMLMouseButtonPressedTranslationMap[this->event.mouseButton.button]; };

	inline EventName getSFMLMouseButtonReleasedEventName() { return EventsManager::SFMLMouseButtonReleasedTranslationMap[this->event.mouseButton.button]; };

	inline EventName getSFMLClosedEventName() { return EventName::CLOSE_WINDOW_BUTTON; };

	inline EventName ignoreSFMLEventType() { return EventName::EVENT_NAMES_COUNT; };

private:
	EventContext context;

	sf::Event event;
	std::unordered_map<EventName, std::vector<AbstractCommand*>> eventCallbacksMap;
	static std::unordered_map <sf::Event::EventType, EventName(EventsManager::*)()> SFMLMapper;

	//Translation Maps
	static std::unordered_map<sf::Keyboard::Key, EventName> SFMLKeyPressedTranslationMap;
	static std::unordered_map<sf::Keyboard::Key, EventName> SFMLKeyReleasedTranslationMap;
	static std::unordered_map<sf::Mouse::Button, EventName> SFMLMouseButtonPressedTranslationMap;
	static std::unordered_map<sf::Mouse::Button, EventName> SFMLMouseButtonReleasedTranslationMap;
};

