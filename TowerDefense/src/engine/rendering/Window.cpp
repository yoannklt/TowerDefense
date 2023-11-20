#include "Window.h"
#include "../../core/GameManager.h"
#include "../events/EventsManager.h"

Window::Window(int width, int height, const char* title) : window(sf::VideoMode(width, height), title) {
	GameManager::eventManager.subscribe<Window>(CLOSE_WINDOW_BUTTON, this, &Window::closeWindow);
}

Window::~Window()
{
}

int Window::closeWindow() {
	this->window.close();
	return 0;
}

int Window::clearWindow() {
	this->window.clear();
	return 0;
}

int Window::drawOnWindow(sf::Drawable* drawable) {
	this->window.draw(*drawable);
	return 0;
}

int Window::display() {
	this->window.display();
	return 0;
}


//sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "BrickBreaker", sf::Style::Fullscreen);
//sf::RenderWindow window(sf::VideoMode(640, 480), "BrickBreaker", sf::Style::Fullscreen);
//sf::RenderWindow window(sf::VideoMode(640, 480), "SFML");