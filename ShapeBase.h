#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector3.hpp>
#include <string>
#include "Vector2d.h"

struct ShapeBase
{
	std::shared_ptr<sf::Texture> mTexture;
	std::string mTexturePath;
	sf::Vector3f colour; //RGB
	Vector2d shapeSize;
};