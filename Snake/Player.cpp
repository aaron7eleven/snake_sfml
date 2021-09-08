#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)

{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);

}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	// Moving left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= speed * deltaTime;
	}

	// Moving Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += speed * deltaTime;
	}

	// Check if idle
	if (movement.x == 0.0f) {
		row = 0; // Idle row in sprite sheet
	}
	else {
		row = 1; // Walking row in sprite sheet
		
		// Check which way we are moving
		if (movement.x > 0.0f) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);

}

void Player::Draw(sf::RenderWindow& window)
{

	window.draw(body);
}
