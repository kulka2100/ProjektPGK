#include "stdafx.h"
#include "Menu.h"

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("font.ttf")) {
		throw std::runtime_error("Nie mozna zaladowac czcionki");
	}

	background = new Background("textury/tlo2.png");

	sf::Text play;
	play.setFont(font);
	play.setString("Play");
	play.setPosition(sf::Vector2f(width / 2.0f - 50.0f, height / 2.0f - 60.0f));
	play.setFillColor(selectedColor);
	menuItems.push_back(play);

	sf::Text maps;
	maps.setFont(font);
	maps.setString("Maps");
	maps.setPosition(sf::Vector2f(width / 2.0f - 50.0f, height / 2.0f));
	maps.setFillColor(unselectedColor);
	menuItems.push_back(maps);

	sf::Text settings;
	settings.setFont(font);
	settings.setString("Settings");
	settings.setPosition(sf::Vector2f(width / 2.0f - 50.0f, height / 2.0f + 60.0f));
	settings.setFillColor(unselectedColor);
	menuItems.push_back(settings);

	sf::Text loading;
	loading.setFont(font);
	loading.setString("Loading");
	loading.setPosition(sf::Vector2f(width / 2.0f - 50.0f, height / 2.0f + 120.0f));
	loading.setFillColor(unselectedColor);
	menuItems.push_back(loading);


	selectedIndex = 0;  // Domyœlnie wybrany pierwszy element
}

Menu::Menu()
{
}


void Menu::draw(sf::RenderWindow& window) {
	background->render(window);
	for (const auto& item : menuItems) {
		window.draw(item);
	}
}


void Menu::moveUp() {
	if (selectedIndex - 1 >= 0) {
		menuItems[selectedIndex].setFillColor(unselectedColor);
		selectedIndex--;
		menuItems[selectedIndex].setFillColor(selectedColor);
	}
}

void Menu::moveDown() {
	if (selectedIndex + 1 < menuItems.size()) {
		menuItems[selectedIndex].setFillColor(unselectedColor);
		selectedIndex++;
		menuItems[selectedIndex].setFillColor(selectedColor);
	}
}

int Menu::getSelectedIndex() const {
	return selectedIndex;
}
