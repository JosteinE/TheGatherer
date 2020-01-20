#include "LandscapeGenerator.h"
#include "EntityManager.h"
#include "RectangleShapeComponent.h"
#include "TileMap.h"
#include <ctime>
#include <vector>
#include "TileMap.h"

LandscapeGenerator::LandscapeGenerator()
{
	// Activate the randomizer.
	srand(static_cast<unsigned int>(time(NULL)));
}

LandscapeGenerator::~LandscapeGenerator()
{
}

std::shared_ptr<TileMap> LandscapeGenerator::constructTileMap(const std::string tileset, int numTileTypes, Vector2d inPosition, Vector2d * inTileSize, Vector2d * inTileSetSize)
{
		// Create our tile map
	std::shared_ptr<TileMap> map = std::make_shared<TileMap>();

		// Generate random numbers ranging from 0 and the number of tiletypes - 1 
		for (int x = 0; x < inTileSetSize->x * inTileSetSize->y; x++)
		{
			map->mTileMapData.map.push_back(rand() % numTileTypes);
		}

		map->mTileMapData.tileset = tileset;
		map->mTileMapData.position = inPosition;
		map->mTileMapData.tileSetSize = *inTileSetSize;
		map->mTileMapData.tileSize = *inTileSize;

		if (!map->load())
		{
			std::cout << "Failed to load the map." << std::endl;
			return nullptr;
		}
		else
		{
			map->setPosition(inPosition.toSf());
			return map;
		}
}
