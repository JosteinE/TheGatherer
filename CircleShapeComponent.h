#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "ShapeBase.h"

struct CircleShapeComponent : ShapeBase
{
	sf::CircleShape* mShape;
};