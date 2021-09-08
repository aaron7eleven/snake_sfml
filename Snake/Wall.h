#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
	public:
		Wall(sf::Vector2f position, sf::Vector2f size);
		~Wall();

		void Draw(sf::RenderWindow& window);
		sf::RectangleShape GetWall() { return wall; }

	private:
		sf::RectangleShape wall;
};

