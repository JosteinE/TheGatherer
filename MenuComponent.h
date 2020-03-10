#pragma once

#include "Vector2d.h"

struct MenuComponent
{
	std::string texturePath;
	std::string fontPath;
	Vector2d position;
	int elementSpacing = 16;
};