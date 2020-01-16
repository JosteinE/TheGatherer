#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include "Vector2d.h"

struct ShapeBase
{
	std::shared_ptr<sf::Texture> mTexture;
	std::string mTexturePath;
	Vector2d shapeSize;
};