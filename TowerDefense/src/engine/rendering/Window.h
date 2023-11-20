#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>


/// <summary>
/// Class Wrapping the sf::RenderWindow into a custom Class
/// </summary>
class Window {
public:
	Window(int width, int height, const char* title = "New Project");
	~Window();
	int closeWindow();
	int clearWindow();
	int drawOnWindow(sf::Drawable* drawable);
	int display();
	inline sf::RenderWindow* getSFMLObject() { return &window; };

private:
	sf::RenderWindow window;
};