#pragma once
#include "Vector2d.h"
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "TileMapComponent.h"
#include <SFML/Graphics/Vertex.hpp>

class Entity;
class EntityManager;
class TileMap;

class LandscapeGenerator
{
public:
	LandscapeGenerator();
	~LandscapeGenerator();

	std::shared_ptr<TileMap> constructTileMap(const std::string tileset, int numTileTypes, Vector2d inPosition, Vector2d* inTileSize, Vector2d* inTileSetSize, bool randTexture = true);

	void shadeTileMap(std::shared_ptr<TileMap> map, unsigned int tileAmount, unsigned int maxShadeExtentX, unsigned int maxShadeExtentY, unsigned int maxShadeAmount, unsigned int shadeSteps);
	void colourTileMap(std::shared_ptr<TileMap> map, unsigned int r, unsigned int g, unsigned int b, unsigned int a, unsigned int tileAmount, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise = false, Vector2d* areaPos = nullptr);
	void mutateTileMap(std::shared_ptr<TileMap> map, unsigned int textureIndex, unsigned int tileAmount, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise = false, Vector2d* areaPos = nullptr);
private:
	void mutateTiles(std::shared_ptr<TileMap> map, unsigned int textureIndex, unsigned int maxTileExtentX, unsigned int maxTileExtentY, bool randomise, Vector2d* areaPos = nullptr);
	void colourQuad(sf::Vertex* quad, unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255);
};

