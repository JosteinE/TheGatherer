#include "EntitySpawner.h"
#include "EntityManager.h"
#include "GeneralDataComponent.h"
#include <ctime>
#include "SpriteComponent.h"
#include "NPCStateComponent.h"

EntitySpawner::EntitySpawner(EntityManager * inEntityM, SpriteManager * inSpriteM, AnimationManager * inAnimM, Vector2d* inDefaultFrameSize)
{
	// Activate the randomizer.
	srand(static_cast<unsigned int>(time(NULL)));
	
	mEntityManager = inEntityM;
	mSpriteManager = inSpriteM;
	mAnimationManager = inAnimM;

	defaultFrameSize = *inDefaultFrameSize;
}

EntitySpawner::~EntitySpawner()
{
}

std::vector<Entity*> EntitySpawner::SpawnEntities(unsigned int type, std::vector<int>* comps, unsigned int layer, Vector2d areaBoxMin, Vector2d areaBoxMax, unsigned int minNumToSpawn, unsigned int maxNumToSpawn, const std::string * texturePath)
{
	int numToSpawn = minNumToSpawn + (rand() % (maxNumToSpawn - minNumToSpawn + 1));

	std::vector<Entity*> spawnedEntities;
	Vector2d spawnPos { (areaBoxMax.x - areaBoxMin.x) * 0.5f + areaBoxMin.x, (areaBoxMax.y - areaBoxMin.y) * 0.5f + areaBoxMin.y };

	for (int i = 1; i <= numToSpawn; i++)
	{
		mEntityManager->createNewEntity(type, layer, comps, true);
		//spawnPos.x = areaBoxMin.x + (rand() % static_cast<int>(areaBoxMax.x - areaBoxMin.x));
		//spawnPos.y = areaBoxMin.y + (rand() % static_cast<int>(areaBoxMax.y - areaBoxMin.y));
		
		Entity* newEntity = mEntityManager->getLastEntity();
		mEntityManager->setEntityPosition(newEntity, &spawnPos);
		mEntityManager->updateEntitySection(newEntity, false);

		if (newEntity->mNPCStateComponent != nullptr)
		{
			newEntity->mNPCStateComponent->restrictedAreaMin = areaBoxMin;
			newEntity->mNPCStateComponent->restrictedAreaMax = areaBoxMax;
			newEntity->mNPCStateComponent->destination = spawnPos;

			newEntity->mNPCStateComponent->areaRestricted = true;
		}

		if (newEntity->mSpriteComponent != nullptr)
		{
			mSpriteManager->createSprite(newEntity->mSpriteComponent, texturePath);

			if (newEntity->mAnimationComponent != nullptr)
			{
				mAnimationManager->buildAnim(newEntity->mAnimationComponent, newEntity->mSpriteComponent, defaultFrameSize);
				mSpriteManager->centerSpriteOrigin(newEntity->mSpriteComponent, newEntity->mAnimationComponent);
			}
			else
				mSpriteManager->centerSpriteOrigin(newEntity->mSpriteComponent);

			newEntity->mSpriteComponent->mSprite->setPosition(sf::Vector2f(spawnPos.x, spawnPos.y));
		}

		spawnedEntities.push_back(newEntity);
	}

	return spawnedEntities;
}

std::vector<Entity*> EntitySpawner::SpawnDefaultNPC(Vector2d * areaBoxMin, Vector2d * areaBoxMax, unsigned int minNumToSpawn, unsigned int maxNumToSpawn)
{
	std::vector<int> comps { ANIMATION_COMPONENT, COLLISION_COMPONENT, COMBAT_COMPONENT, MOVEMENT_COMPONENT, NPC_STATE_COMPONENT, SPRITE_COMPONENT };
	const std::string tPath{ "Assets/Textures/pCharSheet.png" };
	return SpawnEntities(NPC_ENTITY, &comps, 1, *areaBoxMin, *areaBoxMax, minNumToSpawn, maxNumToSpawn, &tPath);
}

