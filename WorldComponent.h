#pragma once
#include "Vector2d.h"

struct WorldComponent
{
	// Window
	float camZoom = 25; // % of how much of the landscape should be visible relative to the window size.
	
	// Map / Tiles
	Vector2d tileSize{ 32.f, 32.f }; // pixel units
	Vector2d tileSetSize{ 10, 10 };
	// Vector2d tileSpacing{ 1.05f, 1.05f };

	const std::string tileSet{ "Assets/Textures/TileMap.png" };
	const int numTileTypes = 3;

	// Player
	const std::string playerTexturePath{ "Assets/Textures/MainKarakterMRustning.png" };
	Vector2d playerSize{ 2.5f, 2.5f };
};