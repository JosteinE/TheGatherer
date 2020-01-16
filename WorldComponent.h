#pragma once
#include "Vector2d.h"

struct WorldComponent
{
	// Window
	float viewSize = 75; // % of how much of the landscape should be visible relative to the window size.

	// Map / Tiles 
	Vector2d tileSize{ 150.f, 150.f };
	Vector2d tileSetSize{ 50, 50 };
	Vector2d tileSpacing{ 1.05f, 1.05f };

	const std::string tileTexture{ "Assets/Textures/grass.bmp" };
	
	// Player
	const std::string playerTexturePath{ "Assets/Textures/MainKarakterMRustning.png" };
	Vector2d playerSize{ 10.f, 10.f };
};