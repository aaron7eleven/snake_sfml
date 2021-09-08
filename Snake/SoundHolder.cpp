#include "SoundHolder.h"

SoundHolder::SoundHolder()
{
}

SoundHolder::~SoundHolder()
{
}

void SoundHolder::AddSound(std::string name, std::string filename)
{
	sf::SoundBuffer soundBuffer;
	if (!soundBuffer.loadFromFile(filename)) {
		std::cout << "Error loading sound: " << filename << std::endl;
	}

	holder.insert(std::make_pair(name, soundBuffer));
}

sf::SoundBuffer* SoundHolder::GetSound(std::string name)
{
	return &holder[name];
}
