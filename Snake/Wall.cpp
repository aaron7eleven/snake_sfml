#include <SFML/Graphics.hpp>
#include "Wall.h"
#include <iostream>

Wall::Wall(sf::Vector2f position, sf::Vector2f size) {
	
	wall.setSize(size);
	wall.setOrigin(wall.getSize() / 2.0f);
	wall.setPosition(position);
}

Wall::~Wall()
{
}

void Wall::Draw(sf::RenderWindow& window)
{
	window.draw(wall);
}
