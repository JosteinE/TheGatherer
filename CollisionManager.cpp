#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "TileMap.h"

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::setCollisionProfile(CollisionComponent * colComp, unsigned int colProfile)
{
	colComp->colProfile = colProfile;
}

bool CollisionManager::isColliding(Vector2d* entPos, CollisionComponent* colComp, std::vector<Vector2d>* otherEntPos)
{
		Vector2d colBoxMin = Vector2d(entPos->x - colComp->colExtentLeft, entPos->y - colComp->colExtentUp);
		Vector2d colBoxMax = Vector2d(entPos->x + colComp->colExtentRight, entPos->y + colComp->colExtentDown);
		for (auto otherMin : *otherEntPos)
		{
			Vector2d otherMax = Vector2d(otherMin.x + 16, otherMin.y + 16);
			if (otherMax.x >= colBoxMin.x && otherMin.x <= colBoxMax.x &&
				otherMax.y >= colBoxMin.y && otherMin.y <= colBoxMax.y)
			{
				colComp->isColliding = true;
				return true;
			}
		}
		colComp->isColliding = false;
		return false;
}

bool CollisionManager::isColliding(Vector2d * entPos, CollisionComponent * colComp, TileMap * map)
{
	std::vector<Vector2d> nearbyTiles;
	std::vector<unsigned int> tilesToExclude;
	switch (colComp->colProfile)
	{
	case UNDEFINED_COLLISION_PROFILE:
		return false;
	case PLAYER_COLLISION_PROFILE:
		tilesToExclude.insert(tilesToExclude.begin(), { 0,4 });
		break;
	case NPC_COLLISION_PROFILE:
		tilesToExclude.insert(tilesToExclude.begin(), { 0,4 });
		break;
	case NIGHT_MOSNTER_COLLISION_PROFILE:
		tilesToExclude.insert(tilesToExclude.begin(), { 0,1,2,3,4 });
		break;
	default:
		break;
	}

	for (unsigned int tileIndex : map->getArea(map->getTileIndex(entPos), 1, 1, true))
	{
		bool tileCanBlock{ true };
		for (unsigned int x : tilesToExclude)
		{
			if (map->getTileTextureIndex(tileIndex) == x)
			{
				tileCanBlock = false;
				break;
			}
		}

		if(tileCanBlock)
			nearbyTiles.push_back(Vector2d(map->getTile(tileIndex)->position.x, map->getTile(tileIndex)->position.y));
	}

	return isColliding(entPos, colComp, &nearbyTiles);
}