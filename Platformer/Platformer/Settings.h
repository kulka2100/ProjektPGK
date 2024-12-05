#pragma once
#include "Menu.h"

class Settings : public Menu
{
private:
	std::vector<sf::Text> settingsItems;
public:
	Settings(float width, float height) {
        if (!font.loadFromFile("font.ttf")) {
            throw std::runtime_error("Nie mozna zaladowac czcionki");
        }

        background = new Background("textury/tlo2.png");

		// Dodanie elementów do menu
		addSettingItem("Latwy", width / 2.0f - 50.0f, height / 2.0f, unselectedColor);
		addSettingItem("Trundy", width / 2.0f + 50.f, height / 2.0f, unselectedColor);

	}


	// Funkcja dodaj¹ca element ustawieñ
	void addSettingItem(const std::string& text, float posX, float posY, const sf::Color& color) {
		sf::Text item;
		item.setFont(font);
		item.setString(text);
		item.setPosition(sf::Vector2f(posX, posY));
		item.setFillColor(color);
		settingsItems.push_back(item);
	}
	void draw(sf::RenderWindow& window) {
		background->render(window);
		for (const auto& item : settingsItems) {
			window.draw(item);
		}
	}
};

