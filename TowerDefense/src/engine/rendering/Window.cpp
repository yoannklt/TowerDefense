#include "Window.h"
#include "../../core/GameManager.h"
#include "../events/EventsManager.h"
#include "../events/AbstractMethodCommand.h"

Window::Window(int width, int height, const char* title) : window(sf::VideoMode(width, height), title) {
	GameManager::instance().getEventsManager()->subscribe(CLOSE_WINDOW_BUTTON, new AbstractMethodCommand<Window>(this, &Window::closeWindow));
}

Window::~Window()
{
}

void Window::closeWindow() {
	this->window.close();
}

void Window::clearWindow() {
	this->window.clear();
}

void Window::drawOnWindow(sf::Drawable* drawable) {
	this->window.draw(*drawable);
}

void Window::display() {
	this->window.display();
}


//sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "BrickBreaker", sf::Style::Fullscreen);
//sf::RenderWindow window(sf::VideoMode(640, 480), "BrickBreaker", sf::Style::Fullscreen);
//sf::RenderWindow window(sf::VideoMode(640, 480), "SFML");