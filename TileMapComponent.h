#pragma once
#include <vector>
#include "Vector2d.h"

struct TileMapComponent
{
	std::vector<int> map;
	std::string tileset;
	Vector2d position;
	Vector2d tileSize;
	Vector2d tileSetSize;
};