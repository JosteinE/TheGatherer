#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

struct HUDComponent
{
	sf::Font mFont;
	sf::Text mText;
	const std::string fontPath = "Assets/Fonts/IndieFlower-Regular.ttf";
	std::string initialText = "";
	sf::Color textColour = sf::Color::White;

	sf::Vector2i textRelativePos{ 0, 0 };
	double textSize = 0.1;
	unsigned int characterSize = 100;
	bool bBold{ true };
};