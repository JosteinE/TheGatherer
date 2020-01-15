#pragma once
#include "Vector2d.h"
#include <vector>

class Entity;
class EntityManager;

class LandscapeGenerator
{
private:
	Vector2d mPosition;
	Vector2d mTileSize;
	Vector2d mTileSetSize;
	Vector2d mTileSpacing;
public:
	LandscapeGenerator(Vector2d* inPosition, Vector2d* inTileSize = nullptr, Vector2d* inTileSetSize = nullptr, Vector2d* inTileSpacing = nullptr);
	~LandscapeGenerator();

	void setPosition(Vector2d* inPosition);
	void setTileSize(Vector2d* inTileSize);
	void setTileSetSize(Vector2d* inTileSetSize);
	void setTileSpacing(Vector2d* inTileSpacing);
	void construct(EntityManager* entM, std::vector<int>* components = nullptr);
};

