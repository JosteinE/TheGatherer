#pragma once
#include <vector>
#include "Vector2d.h"
#include "EntityManager.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "SpawnerComponent.h"

class EntityManager;

class EntitySpawner
{
private:
	Vector2d defaultFrameSize;
	EntityManager* mEntityManager = nullptr;
	SpriteManager* mSpriteManager = nullptr;
	AnimationManager* mAnimationManager = nullptr;
public:
	EntitySpawner(EntityManager* inEntityM, SpriteManager* inSpriteM, AnimationManager* inAnimM, Vector2d* inDefaultFrameSize);

	std::vector<Entity*> SpawnEntities(unsigned int type, std::vector<int>* comps, unsigned int layer, Vector2d areaBoxMin, Vector2d areaBoxMax, unsigned int numToSpawn, const std::string * texturePath = nullptr, bool spreadSpawnPos = false);
	std::vector<Entity*> SpawnDefaultNPC(Vector2d* areaBoxMin, Vector2d* areaBoxMax, unsigned int numToSpawn, const std::string * texturePath = nullptr);
	std::vector<SpawnerComponent*> generateSpawners(unsigned int minSectionID, unsigned int maxSectionID, unsigned int numSpawners, unsigned int minEntPerSection, unsigned int maxEntPerSection, unsigned int npcMaxRange, std::string* texturePath );
	~EntitySpawner();
};

