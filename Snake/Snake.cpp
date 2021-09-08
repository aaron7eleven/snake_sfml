#include <SFML/Graphics.hpp>
#include "Snake.h"
#include <iostream>

Snake::Snake(sf::Vector2f initPos, float bodySize)
{
	// Load snake with texture when created
	//snakeTexture.loadFromFile("./Assets/Art/snake_body_small.png");

	initPosition = initPos;
	this->bodySize = bodySize;

	// Set rectangles for the body
	sf::Vector2f tempPos;

	for (int i = 0; i < initLength; i++) {
		sf::RectangleShape rectShape;
		//rectShape.setTexture(&snakeTexture);
		rectShape.setSize(sf::Vector2f(bodySize, bodySize));
		rectShape.setOrigin(rectShape.getSize()/2.0f);
		tempPos = initPosition + sf::Vector2f(0.0f, (float)i) * bodySize;
		rectShape.setPosition(tempPos);		
		body.push_back(rectShape);
	}

	moveVector = sf::Vector2f(0.0f, -1.0f);

}

Snake::Snake(sf::Texture& snakeTexture, sf::Vector2f initPos, float bodySize)
{
	// Load snake with texture when created
	//snakeTexture.loadFromFile("./Assets/Art/snake_body_small.png");
	//this->snakeTexture = snakeTexture;
	initPosition = initPos;
	this->bodySize = bodySize;

	// Set rectangles for the body
	sf::Vector2f tempPos;

	for (int i = 0; i < initLength; i++) {
		sf::RectangleShape rectShape;
		rectShape.setTexture(&snakeTexture);
		rectShape.setSize(sf::Vector2f(bodySize, bodySize));
		rectShape.setOrigin(rectShape.getSize() / 2.0f);
		tempPos = initPosition + sf::Vector2f(0.0f, (float)i) * bodySize;
		rectShape.setPosition(tempPos);
		body.push_back(rectShape);
	}

	moveVector = sf::Vector2f(0.0f, -1.0f);

}


Snake::~Snake()
{
}

void Snake::Draw(sf::RenderWindow& window)
{
	for (sf::RectangleShape chunk : body)
		window.draw(chunk);

}

void Snake::Move()
{
	// Get last element and insert into front element
	sf::RectangleShape bodyToMove = body.back();
	sf::RectangleShape bodyHead = body.front();
	std::vector<sf::RectangleShape>::iterator iterator;
	iterator = body.begin();

	bodyToMove.setPosition(bodyHead.getPosition() + (moveVector * bodySize));

	if (canGrow) {
		canGrow = false;
	}
	else {
		body.pop_back();
	}
		

	body.insert(iterator, bodyToMove);
	
}

void Snake::Update(float deltaTime) {
	// Moving left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (moveVector != rightVector) {
			moveVector = leftVector;
		}
	}

	// Moving Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (moveVector != leftVector) {
			moveVector = rightVector;
		}
	}

	// Moving Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (moveVector != downVector) {
			moveVector = upVector;
		}
	}

	// Moving Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (moveVector != upVector) {
			moveVector = downVector;
		}
	}

	// Grow snake on demand
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		Grow();
	}

	totalTime += deltaTime;

	if (totalTime >= moveTime) {
		totalTime -= moveTime;
		Move();
	}
}

void Snake::Grow()
{
	canGrow = true;
}

bool Snake::CheckCollison(sf::RectangleShape rectangleShape) {
	//// Collision Detection
	//// AABB - Axis Aligned Bounding Box (from Centered Origin)

	//sf::Vector2f otherPosition = rectangleShape.getPosition();
	//sf::Vector2f otherHalfSize = rectangleShape.getSize() / 2.0f;
	//
	//// Checking with snakes head
	//sf::RectangleShape snakeHead = body[0];
	//sf::Vector2f thisPosition = snakeHead.getPosition();
	//sf::Vector2f thisHalfSize = snakeHead.getSize() / 2.0f;

	//float deltaX = otherPosition.x - thisPosition.x;
	//float deltaY = otherPosition.y - thisPosition.y;

	//float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	//float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	//if (intersectX < 0.0f && intersectY < 0.0f) {
	//	return true;
	//}

	//return false;

	sf::RectangleShape snakeHead = body[0];
	if (snakeHead.getGlobalBounds().intersects(rectangleShape.getGlobalBounds())) {
		return true;
	}
	
	return false;
	
}

void Snake::ResetSnake() {

	// Set rectangles for the body
	sf::Vector2f tempPos;
	
	for (int i = initLength; i < body.size(); i++) {
		body.pop_back();
	}

	//for (int i = 0; i < body.size(); i++) {
	//	sf::RectangleShape rectShape;
	//	rectShape.setTexture(&snakeTexture);
	//	rectShape.setSize(sf::Vector2f(bodySize, bodySize));
	//	rectShape.setOrigin(rectShape.getSize() / 2.0f);
	//	tempPos = initPosition + sf::Vector2f(0.0f, (float)i) * bodySize;
	//	rectShape.setPosition(tempPos);
	//	body.push_back(rectShape);
	//}

	for (int i = 0; i < initLength; i++) {
		sf::RectangleShape rectShape;
		//rectShape.setTexture(&snakeTexture);
		//rectShape.setSize(sf::Vector2f(bodySize, bodySize));
		//rectShape.setOrigin(rectShape.getSize() / 2.0f);
		tempPos = initPosition + sf::Vector2f(0.0f, (float)i) * bodySize;
		rectShape.setPosition(tempPos);
		//body.push_back(rectShape);
	}
}

void Snake::SetTextureToBody() {
	for (int i = 0; i < body.size(); i++) {
		body[i].setTexture(&snakeTexture);
	}
}

void Snake::SetMoveTime(float newMoveTime)
{
	moveTime = newMoveTime;
}



