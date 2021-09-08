#include "Item.h"

Item::Item(sf::Vector2f position, float size)
{
	item.setSize(sf::Vector2f(size, size));
	item.setOrigin(item.getSize() / 2.0f);
	item.setPosition(position);

}

Item::~Item()
{
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(item);
}
