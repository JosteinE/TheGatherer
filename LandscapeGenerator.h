#pragma once
#include "Vector2d.h"
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "TileMapComponent.h"

class Entity;
class EntityManager;
class TileMap;

class LandscapeGenerator
{
public:
	LandscapeGenerator();
	~LandscapeGenerator();

	std::shared_ptr<TileMap> constructTileMap(const std::string tileset, int numTileTypes, Vector2d inPosition, Vector2d* inTileSize, Vector2d* inTileSetSize);
};

