#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{

	public:
		TextureHolder();
		~TextureHolder();
		void AddTexture(std::string name, std::string filename);
		sf::Texture* GetTexture(std::string name);
		void PrintHolder();
		int GetSize() { return holder.size(); }


	private:
		std::map<std::string, sf::Texture> holder;
};

