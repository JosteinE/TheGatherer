#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
struct CollisionComponent
{
	std::vector<sf::Vector2f> colliderVertices;
};