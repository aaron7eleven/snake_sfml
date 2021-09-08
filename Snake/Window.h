#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Window : public sf::RenderWindow
{
	public:
		Window(int windowWidth, int windowHeight);
		~Window();

		//bool isOpen();

	private:
		sf::RenderWindow window;
};

