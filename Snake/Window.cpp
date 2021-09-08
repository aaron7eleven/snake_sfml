#include "Window.h"

Window::Window(int windowWidth, int windowHeight)
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake", sf::Style::Default);
}

Window::~Window()
{
}

//bool Window::isOpen()
//{
//	return window.isOpen();
//}
