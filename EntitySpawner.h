#pragma once
#include <vector>
#include "Vector2d.h"
#include "EntityManager.h"
#include "SpriteManager.h"
#include "AnimationManager.h"

class EntityManager;

class EntitySpawner
{
private:
	Vector2d* defaultFrameSize;
	EntityManager* mEntityManager = nullptr;
	SpriteManager* mSpriteManager = nullptr;
	AnimationManager* mAnimationManager = nullptr;
public:
	EntitySpawner(EntityManager* inEntityM, SpriteManager* inSpriteM, AnimationManager* inAnimM, Vector2d* inDefaultFrameSize);

	std::vector<Entity*> SpawnEntities(std::vector<int>* comps, unsigned int layer, Vector2d areaBoxMin, Vector2d areaBoxMax, unsigned int minNumToSpawn, unsigned int maxNumToSpawn, const std::string * texturePath = nullptr);
	~EntitySpawner();
};

