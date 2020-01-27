#include "EntityManager.h"
#include <iostream>
#include "GeneralDataComponent.h"
#include "ToolComponent.h"
#include "ItemManager.h"
#include "SpriteComponent.h"

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
	removeEntities();
}

void EntityManager::createNewEntity(int layer, bool addGeneralComponent)
{
	Entity* newEntity = new Entity(addGeneralComponent);

	mEntities.push_back(newEntity);
	setEntityLayer(newEntity, layer);
}

void EntityManager::createNewEntity(int layer, std::vector<int>* comps)
{
	Entity* newEntity = new Entity();

	if (comps != nullptr)
		addComponentsToEntity(newEntity, comps);

	mEntities.push_back(newEntity);
	setEntityLayer(newEntity, layer);
}

void EntityManager::createNewItemEntity(ItemManager* itemM, unsigned int itemID, bool isTool, unsigned int itemTier)
{
	createNewEntity(2, true);
	getLastEntity()->addComponent(SPRITE_COMPONENT);
	getLastEntity()->mSpriteComponent->mSprite = new sf::Sprite();

	if (isTool)
	{
		getLastEntity()->addComponent(TOOL_COMPONENT);
		getLastEntity()->mToolComponent->itemID = itemID;
		getLastEntity()->mToolComponent->toolTier = itemTier;
		itemM->assignToolProperties(getLastEntity()->mToolComponent, getLastEntity()->mSpriteComponent);
	}
	else
	{
		getLastEntity()->addComponent(ITEM_COMPONENT);
		itemM->setItemTexture(getLastEntity()->mItemComponent, getLastEntity()->mSpriteComponent);
	}
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

void EntityManager::setEntityLayer(Entity * inEntity, int layer)
{
	if (layer >= 0)
	{
		mLayers[layer].push_back(inEntity);
		inEntity->mGeneralDataComponent->layer = layer;
	}
	else
		std::cout << "Attempted to put the entity on an invalid layer." << std::endl;
}

void EntityManager::removeEntities()
{
	for (auto entity : mEntities)
	{
		delete entity;
	}
	mEntities.clear();
	mEntities.resize(0);
}

Entity * EntityManager::getEntity(int id)
{
	if (mEntities[id] != nullptr)
		return mEntities[id];
	else
		std::cout << "Could not locate an entity with the given id!" << std::endl;
}

Entity * EntityManager::getLastEntity()
{
	return mEntities[mEntities.size()-1];
}

std::vector<Entity*>* EntityManager::getEntities()
{
	return &mEntities;
}

std::vector<Entity*>* EntityManager::getEntitiesFromLayer(unsigned int layer)
{
	return &mLayers[layer];
}
