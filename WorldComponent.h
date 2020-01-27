#pragma once
#include "Vector2d.h"

struct WorldComponent
{
	// Window
	float camZoom = 10; // % of how much of the landscape should be visible relative to the window size.
	
	// Map / Tiles
	Vector2d tileSize{ 16.f, 16.f }; // pixel units
	Vector2d tileSetSize{ 100, 100 };
	const std::string tileSet{ "Assets/Textures/TileMap.png" };
	const int numTileTypes = 3;
	
	// Items
	sf::Vector2u itemSize{ 16.f, 16.f }; // pixel units
	const std::string itemSet{ "Assets/Textures/ItemSet.png" };

	// Player
	const std::string playerTexturePath{ "Assets/Textures/pCharSheet.png" };
	Vector2d playerSpriteSize{ 16.f, 16.f }; // pixel units
	Vector2d playerSize{ 1.f, 1.f };
};