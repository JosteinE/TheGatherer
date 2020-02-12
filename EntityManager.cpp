#include "EntityManager.h"
#include <iostream>
#include "GeneralDataComponent.h"
#include "ToolComponent.h"
#include "ItemManager.h"
#include "SpriteComponent.h"

#include <algorithm>

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
	deleteEntities();
}

void EntityManager::createNewEntity(unsigned int type, int layer, bool addGeneralComponent)
{
	Entity* newEntity = new Entity(type, addGeneralComponent);

	mEntities[type].push_back(newEntity);
	setEntityLayer(newEntity, layer);

	lastEntityCreated = newEntity;
}

void EntityManager::createNewEntity(unsigned int type, int layer, std::vector<int>* comps)
{
	createNewEntity(type, layer, true);

	if (comps != nullptr)
		addComponentsToEntity(lastEntityCreated, comps);
}

void EntityManager::createNewItemEntity(ItemManager* itemM, unsigned int itemID, bool isTool, unsigned int itemTier)
{
	createNewEntity(ITEM_ENTITY, 2, true);
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

void EntityManager::deleteEntity(unsigned int, Entity * inEntity, bool deleteChildren)
{
	std::vector<Entity*>::iterator it = std::find(mEntities[inEntity->mGeneralDataComponent->type].begin(), mEntities[inEntity->mGeneralDataComponent->type].end(), inEntity);
	if (it != mEntities[inEntity->mGeneralDataComponent->type].end())
		mEntities[inEntity->mGeneralDataComponent->type].erase(it);

	if (deleteChildren)
	{
		for (Entity* child : *inEntity->getChildren())
		{
			deleteEntity(child->mGeneralDataComponent->type, child, true);
		}
		inEntity->removeChildren();
	}

	delete inEntity;
}

void EntityManager::deleteEntities()
{
	for (auto entityType : mEntities)
	{
		for (auto entity : entityType.second)
		{
			delete entity;
		}

		mEntities[entityType.first].clear();
		mEntities[entityType.first].resize(0);
	}
	mEntities.clear();
}

void EntityManager::deleteEntities(std::vector<Entity*> inEntities, bool deleteChildren)
{
	for (Entity* entity : inEntities)
		deleteEntity(entity->mGeneralDataComponent->type, entity, deleteChildren);
}

Entity * EntityManager::getEntity(unsigned int type, int id)
{
	return mEntities[type][id];
}

Entity * EntityManager::getLastEntity()
{
	return lastEntityCreated;
}

std::vector<Entity*>* EntityManager::getEntities(unsigned int type)
{
	return &mEntities[type];
}

std::vector<Entity*>* EntityManager::getEntitiesFromLayer(unsigned int layer)
{
	return &mLayers[layer];
}

void EntityManager::updateChildren(Entity * inEntity)
{
	for (Entity *child : *inEntity->getChildren())
	{
		child->mGeneralDataComponent->position = inEntity->mGeneralDataComponent->position;
	}
}
