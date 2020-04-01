#pragma once
#include "Vector2d.h"
#include <vector>

struct CollisionComponent;

class TileMap;

enum COLLISION_PROFILE
{
	UNDEFINED_COLLISION_PROFILE,
	PLAYER_COLLISION_PROFILE,
	NPC_COLLISION_PROFILE,
	NIGHT_MOSNTER_COLLISION_PROFILE,
};

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void setCollisionProfile(CollisionComponent* colComp, unsigned int colProfile);

	bool isColliding(Vector2d* entPos, CollisionComponent* colComp, std::vector<Vector2d>* otherEntPos);
	bool isColliding(Vector2d* entPos, CollisionComponent* colComp, TileMap* map);
};