#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Wall.h"
#include "Item.h"
#include "TextureHolder.h"
#include "SoundHolder.h"
#include "UI.h"
#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>

static const float WINDOW_HEIGHT = 512.0f;
static const float WINDOW_WIDTH = 512.0f;
static const float VIEW_HEIGHT = 512.0f;
static const float VIEW_WIDTH = 512.0f;

static const float GRID_SIZE = 16.0f;

class Game
{

	public:
		Game();
		~Game();

		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);
		void Run();
		void Gameplay();
		void RestartGame();
		void UpdateGameOverUI();
		void UpdateMainMenuUI();
		void LateInit();

	private:
		Snake snake;
		std::vector<Wall> walls;
		Item item;
		bool isGameOver = false;
		bool isMainMenu = true;
		sf::Font font;
		sf::Text gameOverText;
		TextureHolder textureHolder;
		SoundHolder soundHolder;
		sf::Sound sound;
		sf::Music music;
		UI gameOverUI;
		UI mainMenuUI;
		bool isHardMode = false;
		

};

