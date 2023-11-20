#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include "EventsNames.h"

class VoidClass {};


typedef enum EventCallbackReturns {
	SUCCESS = 0,
	FAILURE,
	STOP_PROPAGATE,
	EVENT_CALLBACK_RETURNS_AMOUNT
} EventCallbackReturn;

using EventCallback = std::function<int()>;

struct EventCallbackData
{
	void* instanceAdress;
	void(VoidClass::* methodPointer)();
	EventCallback callback;
};

class EventsManager
{
public:
	EventsManager();
	~EventsManager();

	template<typename T>
	void subscribe(EventName eventName, T* instanceAdress, int(T::* methodPointer)())
	{
		EventCallbackData eventCallbackData;
		eventCallbackData.instanceAdress = (void*)instanceAdress;
		eventCallbackData.methodPointer = (void(VoidClass::*)()) methodPointer;
		eventCallbackData.callback = std::bind(methodPointer, instanceAdress);
		eventCallbacksMap[eventName].push_back(eventCallbackData);
	}

	template<typename T>
	void unsubscribe(EventName eventName, T* instanceAdress, int(T::* methodPointer)())
	{
		std::vector<EventCallbackData>* eventCallbacks = &eventCallbacksMap[eventName];
		void* castedInstanceAdress = (void*)instanceAdress;
		void(VoidClass:: * castedMethodPointer)() = (void(VoidClass::*)()) methodPointer;
		int index = 0;
		for (EventCallbackData callbackData : *eventCallbacks) {
			if (callbackData.instanceAdress == castedInstanceAdress && callbackData.methodPointer == castedMethodPointer) {
				eventCallbacks->erase(eventCallbacks->begin() + index);
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
	sf::Event event;
	std::unordered_map<EventName, std::vector<EventCallbackData>> eventCallbacksMap;
	static std::unordered_map <sf::Event::EventType, EventName(EventsManager::*)()> SFMLMapper;

	//Translation Maps
	static std::unordered_map<sf::Keyboard::Key, EventName> SFMLKeyPressedTranslationMap;
	static std::unordered_map<sf::Keyboard::Key, EventName> SFMLKeyReleasedTranslationMap;
	static std::unordered_map<sf::Mouse::Button, EventName> SFMLMouseButtonPressedTranslationMap;
	static std::unordered_map<sf::Mouse::Button, EventName> SFMLMouseButtonReleasedTranslationMap;
};

