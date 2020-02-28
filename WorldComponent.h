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
	bool centerMap{ false };
	Vector2d tileSetSize{ 100, 100 };
	const std::string tileSet{ "Assets/Textures/TileMap.png" };
	const int numTileTypes = 3;

	// Map Sections
	Vector2d sectionSize{ 320, 320 };
	// NPC Spawners
	int minSectionID = 2;
	int maxSectionID = 100;
	int numSpawners = 50;
	int minEntPerSection = 2;
	int maxEntPerSection = 5;
	int npcMaxRange = 100;
	std::string spawnerTexPath{ "Assets/Textures/pCharSheet.png" };
	
	// Items
	const std::string itemSet{ "Assets/Textures/ItemSet.png" };

	// Player
	const std::string playerTexturePath{ "Assets/Textures/pCharSheet.png" };
	Vector2d playerSize{ 1.f, 1.f };
};