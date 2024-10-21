#pragma once
#include "Background.h"
class Menu
{
private:
	sf::Font font;
	std::vector<sf::Text> menuItems;
	int selectedIndex;
	const sf::Color selectedColor = sf::Color::Red;
	const sf::Color unselectedColor = sf::Color::White;

	Background *background;

public:
	Menu(float width, float height);

	void draw(sf::RenderWindow& window);

	void moveUp();

	void moveDown();

	int getSelectedIndex() const;
};

