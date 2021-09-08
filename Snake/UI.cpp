#include "UI.h"
#include <iostream>

UI::UI(sf::Vector2f viewSize)
{
	if (!font.loadFromFile("./Assets/Font/PressStart2P-Regular.ttf")) {
		// Do Error checking
	}

	this->viewSize = viewSize;

	for (int i = 0; i < MAX_NUM_OF_TEXT_ITEMS; i++) {
		menuElements[i].setFont(font);
		menuElements[i].setString("");
		menuElements[i].setCharacterSize(24);
	}

	CenterText();
}

UI::~UI()
{
}

void UI::MoveUp()
{
}

void UI::MoveDown()
{
}

void UI::SetText(std::string* menuText) {
	for (int i = 0; i < MAX_NUM_OF_TEXT_ITEMS; i++) {
		this->menuText[i] = menuText[i];
	}
	UpdateMenuElementsText();
}

void UI::SetText(int element, std::string text) {
	if (element < MAX_NUM_OF_TEXT_ITEMS) {
		menuText[element] = text;
	}
	UpdateMenuElementsText();
}

void UI::UpdateMenuElementsText() {
	for (int i = 0; i < MAX_NUM_OF_TEXT_ITEMS; i++) {
		menuElements[i].setString(menuText[i]);
	}
}

void UI::CenterText() {

	for (int i = 0; i < MAX_NUM_OF_TEXT_ITEMS; i++) {
		sf::FloatRect textRect = menuElements[i].getLocalBounds();
		menuElements[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		menuElements[i].setPosition(sf::Vector2f(viewSize.x / 2.0f, viewSize.y / 4.0f * (float) (i+1)));
	}
}

void UI::Draw(sf::RenderWindow& window) {
	
	for (int i = 0; i < MAX_NUM_OF_TEXT_ITEMS; i++) {
		window.draw(menuElements[i]);
	}	
}
