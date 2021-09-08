#pragma once
#include <SFML/Graphics.hpp>

class Item
{

	public:
		Item(sf::Vector2f position, float size);
		~Item();

		void Draw(sf::RenderWindow& window);
		sf::RectangleShape GetItem() { return item; }

	private:
		sf::RectangleShape item;
};

