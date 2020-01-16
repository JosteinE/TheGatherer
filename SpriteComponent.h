#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "ShapeBase.h"

struct SpriteComponent : ShapeBase
{
	sf::Sprite* mSprite;
};