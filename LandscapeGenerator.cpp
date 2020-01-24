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

std::shared_ptr<TileMap> LandscapeGenerator::constructTileMap(const std::string tileset, int numTileTypes, Vector2d inPosition, Vector2d * inTileSize, Vector2d * inTileSetSize, bool randTexture)
{
	// Create our tile map
	std::shared_ptr<TileMap> map = std::make_shared<TileMap>();

	if (randTexture)
	{
		// Generate random numbers ranging from 0 and the number of tiletypes - 1 
		for (int x = 0; x < inTileSetSize->x * inTileSetSize->y; x++)
		{
			map->mTileMapData.map.push_back(rand() % numTileTypes);
		}
	}
	else
	{
		for (int x = 0; x < inTileSetSize->x * inTileSetSize->y; x++)
		{
			map->mTileMapData.map.push_back(0);
		}
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

void LandscapeGenerator::shadeTileMap(std::shared_ptr<TileMap> map, unsigned int tileAmount, unsigned int maxShadeExtentX, unsigned int maxShadeExtentY, unsigned int maxShadeAmount, unsigned int shadeSteps)
{
	int mapSize = map->mTileMapData.tileSetSize.x * map->mTileMapData.tileSetSize.y;
	int amountToShade = mapSize / 100 * tileAmount;
	int shadeAmount = maxShadeAmount / shadeSteps; 

	for (unsigned int i = 0; i < amountToShade; i++)
	{
		for (unsigned int tileIndex : map->getArea(rand() % mapSize, rand() % maxShadeExtentX, rand() % maxShadeExtentY, true))
		{
			sf::Vertex* quad = map->getTile(tileIndex);
			if (quad[0].color.r >= 255 - maxShadeAmount + shadeAmount)
			{
				colourQuad(quad, quad[0].color.r - shadeAmount, quad[0].color.g - shadeAmount, quad[0].color.b - shadeAmount);
			}
		}
	}
}

void LandscapeGenerator::colourTileMap(std::shared_ptr<TileMap> map, unsigned int r, unsigned int g, unsigned int b, unsigned int a, unsigned int tileAmount, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise, Vector2d* areaPos)
{
	int amountToColour = ((map->mTileMapData.tileSetSize.x * map->mTileMapData.tileSetSize.y) / 100) * tileAmount;

	for (unsigned int i = 0; i < amountToColour; i++)
	{
		for (unsigned int tileIndex : map->getArea(rand() % static_cast<int>(map->mTileMapData.tileSetSize.x * map->mTileMapData.tileSetSize.y), rand() % maxTileExtentX, rand() % maxTileExtentY, true))
		{
			colourQuad(map->getTile(tileIndex), r, g, b, a);
		}
	}
}

void LandscapeGenerator::mutateTileMap(std::shared_ptr<TileMap> map, unsigned int textureIndex, unsigned int tileAmount, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise, Vector2d* areaPos)
{
	if (areaPos == nullptr)
	{
		int amountToTexture = ((map->mTileMapData.tileSetSize.x * map->mTileMapData.tileSetSize.y) / 100) * tileAmount;

		for (unsigned int i = 0; i < amountToTexture; i++)
		{
			mutateTiles(map, textureIndex, maxTileExtentX, maxTileExtentY, randomise);
		}
	}
	else
		mutateTiles(map, textureIndex, maxTileExtentX, maxTileExtentY, randomise, areaPos);
}

void LandscapeGenerator::mutateTiles(std::shared_ptr<TileMap> map, unsigned int textureIndex, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise, Vector2d * areaPos)
{
	int startIndex;
	if (areaPos == nullptr)
		startIndex = rand() % static_cast<int>(map->mTileMapData.tileSetSize.x * map->mTileMapData.tileSetSize.y);
	else
		startIndex = map->getTileIndex(areaPos);

	if (randomise)
	{
		for (unsigned int tileIndex : map->getArea(startIndex, rand() % maxTileExtentX, rand() % maxTileExtentY, true))
		{
			map->setTileTexture(tileIndex, textureIndex);
		}
	}
	else
	{
		for (unsigned int tileIndex : map->getArea(startIndex, maxTileExtentX, maxTileExtentY, true))
		{
			map->setTileTexture(tileIndex, textureIndex);
		}
	}
}

void LandscapeGenerator::colourQuad(sf::Vertex * quad, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	for (int i = 0; i < 4; i++)
	{
		quad[i].color.r = r;
		quad[i].color.g = g;
		quad[i].color.b = b;
		quad[i].color.a = a;
	}
}
