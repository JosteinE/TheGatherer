#pragma once
#include "Vector2d.h"
#include <vector>

struct CollisionComponent;

class TileMap;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	bool isColliding(Vector2d* entPos, CollisionComponent* colComp, std::vector<Vector2d>* otherEntPos);
	bool isColliding(Vector2d* entPos, CollisionComponent* colComp, TileMap* map);
};