#pragma once
#include "Vector2d.h"

struct WorldComponent
{
	// Window
	float camZoom = 10; // % of how much of the landscape should be visible relative to the window size.
	
	// Map / Tiles
	Vector2d tileSize{ 10.f, 10.f };
	Vector2d tileSetSize{ 50, 50 };
	Vector2d tileSpacing{ 1.1f, 1.1f };

	const std::string tileTexture{ "Assets/Textures/grass.bmp" };

	// Player
	const std::string playerTexturePath{ "Assets/Textures/MainKarakterMRustning.png" };
	Vector2d playerSize{ 1.f, 1.f };
};