#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Collider.h"

class Snake
{

	public:
		Snake(sf::Vector2f initPos, float bodySize);
		Snake(sf::Texture& snakeTexture, sf::Vector2f initPos, float bodySize);
		~Snake();

		void Draw(sf::RenderWindow& window);
		void Move();
		void Update(float deltaTime);
		void Grow();
		bool CheckCollison(sf::RectangleShape rectangleShape);
		sf::RectangleShape GetHead() { return body[0]; }
		std::vector<sf::RectangleShape> GetSnakeBody() { return body; }
		int Length() { return body.size(); }
		sf::Texture GetTexture() { return snakeTexture; }
		void SetTexture(sf::Texture* texture) { snakeTexture = *texture; }
		void SetTextureToBody();
		void ResetSnake();
		void SetMoveTime(float newMoveTime);
		float GetMoveTime() { return moveTime; };

	private:
		sf::Texture snakeTexture;
		float bodySize = 16.0f;
		std::vector<sf::RectangleShape> body;
		//std::vector<Collider> bodyCollider;
		int initLength = 3;
		sf::Vector2f initPosition = sf::Vector2f(0.0f, 0.0f);
		sf::Vector2f moveVector;
		float totalTime = 0.0f;
		float moveTime = 0.1f;
		bool canGrow = false;
		sf::Vector2f leftVector		= sf::Vector2f(-1.0f, 0.0f);
		sf::Vector2f rightVector	= sf::Vector2f(1.0f, 0.0f);
		sf::Vector2f upVector		= sf::Vector2f(0.0f, -1.0f);
		sf::Vector2f downVector		= sf::Vector2f(0.0f, 1.0f);
};

