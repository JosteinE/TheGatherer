#pragma once
#include "Vector2d.h"

struct WorldComponent
{
	// Window
	double camZoom = 0.1;
	
	// Text / Font 
	const std::string fontPath = "Assets/Fonts/IndieFlower-Regular.ttf";

	// Sprite standard
	Vector2d spriteSize{ 16.f, 16.f }; // pixel units

	// Map / Tiles
	Vector2d tileSetSize{ 100, 100 };
	const std::string tileSet{ "Assets/Textures/TileMap.png" };
	const int numTileTypes = 3;
	
	// Items
	const std::string itemSet{ "Assets/Textures/ItemSet.png" };

	// Player
	const std::string playerTexturePath{ "Assets/Textures/pCharSheet.png" };
	Vector2d playerSize{ 1.f, 1.f };
};