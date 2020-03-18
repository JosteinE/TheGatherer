#pragma once
#include <SFML/Graphics/Color.hpp>
#include "Vector2d.h"

struct MenuComponent
{
	sf::Color backgroundColour{ 255, 255, 155, 255 };
	sf::Color defaultButtonOutlineColour{ 0, 0, 0, 255 };
	sf::Color buttonHighlightColour{ 255, 255, 245, 255 };
	sf::Color buttonHighlightBorderColour{ 255, 255, 200, 255 };

	std::string texturePath;
	std::string fontPath;
	Vector2d position;
	int elementSpacing = 16;
};