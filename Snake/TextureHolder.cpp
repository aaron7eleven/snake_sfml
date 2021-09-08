#include "TextureHolder.h"
#include <iostream>

TextureHolder::TextureHolder()
{
}

TextureHolder::~TextureHolder()
{
}

void TextureHolder::AddTexture(std::string name, std::string filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename)) {
		std::cout << "Error loading texture: " << filename << std::endl;
	}
	
	holder.insert(std::make_pair(name, texture));
}

sf::Texture* TextureHolder::GetTexture(std::string name)
{
	return &holder[name];
}
