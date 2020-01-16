#include "EntityManager.h"
#include <iostream>
#include "GeneralDataComponent.h"

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
	removeEntities();
}

void EntityManager::addNewEntity(unsigned int layer, std::vector<int>* comps)
{
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>();

	if (comps != nullptr)
		addComponentsToEntity(newEntity.get(), comps);

	assignID(newEntity);

	setEntityLayer(newEntity.get(), layer);
	mLastEntityCreated = newEntity.get();
}

void EntityManager::addComponentToEntity(Entity * inEntity, int comp)
{
	inEntity->addComponent(comp);
}

void EntityManager::addComponentsToEntity(Entity * inEntity, std::vector<int> * comps)
{
	for (auto comp : *comps)
	{
		addComponentToEntity(inEntity, comp);
	}
}

void EntityManager::setEntityLayer(Entity * inEntity, unsigned int layer)
{
	if (layer >= 0)
	{
		mLayers[layer].push_back(inEntity->mGeneralDataComponent->ID);
		inEntity->mGeneralDataComponent->layer = layer;
	}
	else
		std::cout << "Attempted to put the entity on an invalid layer." << std::endl;
}

void EntityManager::removeEntity(Entity * inEntity)
{
	mEntities.erase(inEntity->mGeneralDataComponent->ID);
	
	// Erase from layer
	std::vector<unsigned int>::iterator it;
	it = std::find(mLayers[inEntity->mGeneralDataComponent->layer].begin(),
				   mLayers[inEntity->mGeneralDataComponent->layer].end(),
				   inEntity->mGeneralDataComponent->ID);
	if (it != mLayers[inEntity->mGeneralDataComponent->layer].end())
		mLayers[inEntity->mGeneralDataComponent->layer].erase(it);
}

void EntityManager::removeEntity(unsigned int inID)
{
}

void EntityManager::removeEntities()
{
	mEntities.clear();
	mLayers.clear();
}

std::shared_ptr<Entity> EntityManager::getEntity(unsigned int id)
{
	if (mEntities[id] != nullptr)
		return mEntities[id];
	else
		std::cout << "Tried to return entity(" << id << ") but it does not exist" << std::endl;
	return nullptr;
}

Entity* EntityManager::getLastEntity()
{
	return mLastEntityCreated;
}

std::vector<unsigned int>* EntityManager::getEntitiesFromLayer(unsigned int layer)
{
	return &mLayers[layer];
}

void EntityManager::assignID(std::shared_ptr<Entity> inEntity)
{
	if (!removedIDs.empty())
	{
		mEntities[removedIDs[0]] = inEntity;
		inEntity->mGeneralDataComponent->ID = removedIDs[0];
		removedIDs.erase(removedIDs.begin());
	}
	else if (mEntities.empty())
	{
		mEntities[1] = inEntity;
		inEntity->mGeneralDataComponent->ID = 1;
	}
	else
	{
		mEntities[mEntities.size() + 1] = inEntity;
		inEntity->mGeneralDataComponent->ID = mEntities.size() + 1;
	}
}
