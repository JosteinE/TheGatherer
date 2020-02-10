#include "EntitySpawner.h"
#include "EntityManager.h"
#include "GeneralDataComponent.h"
#include <ctime>
#include "SpriteComponent.h"

EntitySpawner::EntitySpawner(EntityManager * inEntityM, SpriteManager * inSpriteM, AnimationManager * inAnimM, Vector2d* inDefaultFrameSize)
{
	// Activate the randomizer.
	srand(static_cast<unsigned int>(time(NULL)));
	
	mEntityManager = inEntityM;
	mSpriteManager = inSpriteM;
	mAnimationManager = inAnimM;

	defaultFrameSize = inDefaultFrameSize;
}

EntitySpawner::~EntitySpawner()
{
}

std::vector<Entity*> EntitySpawner::SpawnEntities(std::vector<int>* comps, unsigned int layer, Vector2d areaBoxMin, Vector2d areaBoxMax, unsigned int minNumToSpawn, unsigned int maxNumToSpawn, const std::string * texturePath)
{
	int numToSpawn = minNumToSpawn + (rand() % (maxNumToSpawn - minNumToSpawn));

	std::vector<Entity*> spawnedEntities;

	for (int i = 1; i <= numToSpawn; i++)
	{
		mEntityManager->createNewEntity(layer, comps);
		Vector2d spawnPos;
		spawnPos.x = areaBoxMin.x + (rand() % static_cast<int>(areaBoxMax.x - areaBoxMin.x));
		spawnPos.y = areaBoxMin.y + (rand() % static_cast<int>(areaBoxMax.y - areaBoxMin.y));
		
		Entity* newEntity = mEntityManager->getLastEntity();
		newEntity->mGeneralDataComponent->position = spawnPos;

		if (newEntity->mSpriteComponent != nullptr)
		{
			mSpriteManager->createSprite(newEntity->mSpriteComponent, texturePath);

			if (newEntity->mAnimationComponent != nullptr)
			{
				mAnimationManager->buildAnim(newEntity->mAnimationComponent, newEntity->mSpriteComponent, *defaultFrameSize);
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
