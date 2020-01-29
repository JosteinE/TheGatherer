#include "LandscapeGenerator.h"
#include "EntityManager.h"
#include "RectangleShapeComponent.h"
#include "TileMap.h"
#include <ctime>
#include <vector>
#include "TileMap.h"
#include <SFML/Graphics/Vertex.hpp>

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
	int amountToShade = mapSize * 0.01 * tileAmount;
	int shadeAmount = maxShadeAmount / shadeSteps; 

	for (unsigned int i = 0; i < amountToShade; i++)
	{
		for (unsigned int tileIndex : map->getArea(rand() % mapSize, rand() % maxShadeExtentX, rand() % maxShadeExtentY, true))
		{
			sf::Vertex* quad = map->getTile(tileIndex);
			if (quad[0].color.r >= 255 - maxShadeAmount + shadeAmount)
			{
				map->setTileColour(tileIndex, quad[0].color.r - shadeAmount, quad[0].color.g - shadeAmount, quad[0].color.b - shadeAmount);
			}
		}
	}
}

void LandscapeGenerator::colourShadeTileMap(std::shared_ptr<TileMap> map, unsigned int r, unsigned int g, unsigned int b, unsigned int a, unsigned int tileAmount, unsigned int maxTileExtentX, unsigned int maxTileExtentY, unsigned int shadeSteps, Vector2d* areaPos)
{
	if (shadeSteps <= 0)
		shadeSteps = 1;
	int redShadeAmount = r / shadeSteps;
	int greenShadeAmount = g / shadeSteps;
	int blueShadeAmount = b / shadeSteps;
	int alphaShadeAmount = a / shadeSteps;

	if (areaPos == nullptr)
	{
		int mapSize = map->mTileMapData.tileSetSize.x * map->mTileMapData.tileSetSize.y;
		int amountToShade = mapSize * 0.01 * tileAmount;

		for (unsigned int i = 0; i < amountToShade; i++)
		{
			unsigned int area = rand() % mapSize;
			unsigned int xExtent = rand() % maxTileExtentX;
			unsigned int yExtent = rand() % maxTileExtentY;
			for (unsigned int step = 0; step < shadeSteps; step++)
			{
				for (unsigned int tileIndex : map->getArea(area, xExtent - step, yExtent - step, true))
				{
					sf::Vertex* quad = map->getTile(tileIndex);
					int newRed = quad[0].color.r - redShadeAmount;
					int newGreen = quad[0].color.g - greenShadeAmount;
					int newBlue = quad[0].color.b - blueShadeAmount;
					int newAlpha = quad[0].color.a - alphaShadeAmount;

					if (quad[0].color.r < 255 - r + redShadeAmount)
						newRed = 255 - r;
					if (quad[0].color.g < 255 - g + greenShadeAmount)
						newGreen = 255 - g;
					if (quad[0].color.b < 255 - b + blueShadeAmount)
						newBlue = 255 - b;
					if (quad[0].color.a < 255 - a + alphaShadeAmount)
						newAlpha = 255 - a;

					map->setTileColour(tileIndex, newRed, newGreen, newBlue, newAlpha);
				}
			}
		}
	}
	else
	{
		for (unsigned int step = 0; step < shadeSteps; step++)
		{
			for (unsigned int tileIndex : map->getArea(map->getTileIndex(areaPos), maxTileExtentX - step, maxTileExtentY - step, true))
			{
				sf::Vertex* quad = map->getTile(tileIndex);
				int newRed = quad[0].color.r - redShadeAmount;
				int newGreen = quad[0].color.g - greenShadeAmount;
				int newBlue = quad[0].color.b - blueShadeAmount;
				int newAlpha = quad[0].color.a - alphaShadeAmount;
				
				if (quad[0].color.r < 255 - r + redShadeAmount)
					newRed = 255 - r;
				if (quad[0].color.g < 255 - g + greenShadeAmount)
					newGreen = 255 - g;
				if (quad[0].color.b < 255 - b + blueShadeAmount)
					newBlue = 255 - b;
				if (quad[0].color.a < 255 - a + alphaShadeAmount)
					newAlpha = 255 - a;

				map->setTileColour(tileIndex, newRed, newGreen, newBlue, newAlpha);
			}
		}
	}
}

void LandscapeGenerator::colourTileMap(std::shared_ptr<TileMap> map, unsigned int r, unsigned int g, unsigned int b, unsigned int a, unsigned int tileAmount, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise, Vector2d* areaPos)
{
	int amountToColour = ((map->mTileMapData.tileSetSize.x * map->mTileMapData.tileSetSize.y) / 100) * tileAmount;

	if (areaPos == nullptr)
	{
		for (unsigned int i = 0; i < amountToColour; i++)
		{
			colourTiles(map, r, g, b, a, maxTileExtentX, maxTileExtentY, randomise);
		}
	}
	else
	{
		colourTiles(map, r, g, b, a, maxTileExtentX, maxTileExtentY, randomise, areaPos);
	}
}

void LandscapeGenerator::textureTileMap(std::shared_ptr<TileMap> map, unsigned int textureIndex, unsigned int tileAmount, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise, Vector2d* areaPos)
{
	if (areaPos == nullptr)
	{
		int amountToTexture = ((map->mTileMapData.tileSetSize.x * map->mTileMapData.tileSetSize.y) / 100) * tileAmount;

		for (unsigned int i = 0; i < amountToTexture; i++)
		{
			textureTiles(map, textureIndex, maxTileExtentX, maxTileExtentY, randomise);
		}
	}
	else
		textureTiles(map, textureIndex, maxTileExtentX, maxTileExtentY, randomise, areaPos);
}

void LandscapeGenerator::textureTiles(std::shared_ptr<TileMap> map, unsigned int textureIndex, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise, Vector2d * areaPos)
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

void LandscapeGenerator::colourTiles(std::shared_ptr<TileMap> map, unsigned int r, unsigned int g, unsigned int b, unsigned int a, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise, Vector2d * areaPos)
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
			map->setTileColour(tileIndex, r, g, b, a);
		}
	}
	else
	{
		for (unsigned int tileIndex : map->getArea(startIndex, maxTileExtentX, maxTileExtentY, true))
		{
			map->setTileColour(tileIndex, r, g, b, a);
		}
	}
}
