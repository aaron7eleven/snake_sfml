#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <map>

class SoundHolder
{

public:
	SoundHolder();
	~SoundHolder();
	void AddSound(std::string name, std::string filename);
	sf::SoundBuffer* GetSound(std::string name);
	int GetSize() { return holder.size(); }


private:
	std::map<std::string, sf::SoundBuffer> holder;
};

