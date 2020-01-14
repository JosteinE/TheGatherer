#pragma once
#include <SFML/System/Vector2.hpp>
struct GeneralDataComponent
{
	unsigned int ID = 0;
	std::string name = "Entity";
	sf::Vector2f position{ 0.f, 0.f };
};