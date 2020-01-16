#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "ShapeBase.h"

struct RectangleShapeComponent : ShapeBase
{
	sf::RectangleShape* mShape;
};