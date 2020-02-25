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

void EntityManager::createNewEntity(unsigned int type, int layer, bool addGeneralComponent, bool isTemp)
{
	Entity* newEntity = new Entity(type, addGeneralComponent);

	setEntityLayer(newEntity->mGeneralDataComponent, layer);
	newEntity->mGeneralDataComponent->tempEntity = isTemp;

	lastEntityCreated = newEntity;
}

void EntityManager::createNewEntity(unsigned int type, int layer, std::vector<int>* comps, bool isTemp)
{
	createNewEntity(type, layer, true, isTemp);

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

void EntityManager::setEntityLayer(GeneralDataComponent * inEntityComp, int layer)
{
	if (layer >= 0)
	{
		//mLayers[layer].push_back(inEntity);
		inEntityComp->layer = layer;
	}
	else
		std::cout << "Attempted to put the entity on an invalid layer." << std::endl;
}

bool EntityManager::eraseEntity(Entity * inEntity)
{
	std::vector<Entity*>::iterator it = std::find(mEntities[inEntity->mGeneralDataComponent->section].begin(), mEntities[inEntity->mGeneralDataComponent->section].end(), inEntity);
	if (it != mEntities[inEntity->mGeneralDataComponent->section].end())
	{
		mEntities[inEntity->mGeneralDataComponent->section].erase(it);
		return true;
	}
	else
		return false;
}

void EntityManager::deleteEntity(Entity * inEntity, bool deleteChildren)
{
	if (eraseEntity(inEntity))
	{
		if (deleteChildren)
		{
			for (Entity* child : *inEntity->getChildren())
			{
				deleteEntity(child, true);
			}
			inEntity->removeChildren();
		}

		delete inEntity;
	}
	else
	{
		std::cout << "Failed to erase the entity!" << std::endl;
	}
}

void EntityManager::deleteEntities()
{
	for (auto entityType : mEntities)
	{
		for (auto entity : entityType.second)
		{
			deleteEntity(entity, true);
		}

		mEntities[entityType.first].clear();
		mEntities[entityType.first].resize(0);
	}
	mEntities.clear();
}

void EntityManager::deleteEntities(std::vector<Entity*> inEntities, bool deleteChildren)
{
	for (Entity* entity : inEntities)
		deleteEntity(entity, deleteChildren);
}

std::vector<Entity*>* EntityManager::getRenderSection(Vector2d * position)
{
	std::pair<int, int> pos = getSectionPair(position);
	int section = getSection(&pos);

	if (section == 0)
	{
		addSection(&pos);
		section = getSection(getSectionPair(position));
		updateSection(section);
	}
	
	if (mCurrentSection != section)
	{
		deleteSectionTempEntities(mCurrentSection);
		refreshSection(mCurrentSection);
		setCurrentSection(section);
		std::cout << "Current section: " << mCurrentSection << std::endl;
	}

	return &mEntities[mCurrentSection];
}

int EntityManager::getCurrentSectionIndex()
{
	return mCurrentSection;
}

void EntityManager::setEntitySection(GeneralDataComponent * inEntityComp, int section)
{
	inEntityComp->section = section;
}

int EntityManager::getSection(std::pair<int, int>* position)
{
	return mSections[*position];
}

int EntityManager::getSection(std::pair<int, int> position)
{
	return mSections[position];
}

std::pair<int, int> EntityManager::getSectionPair(Vector2d * position)
{
	return std::pair<int, int>(static_cast<int>(position->x / sectionSize.x), static_cast<int>(position->y / sectionSize.y));
}

void EntityManager::addSection(std::pair<int, int> * position)
{
	mSections[*position] = mSections.size();
}

void EntityManager::setCurrentSection(int section)
{
	mCurrentSection = section;
}

void EntityManager::updateSection(int section)
{
	for (std::pair<unsigned int, std::vector<Entity*>> entityTypes : mEntities)
	{
		for (Entity* entity : entityTypes.second)
		{
			if (getSection(&getSectionPair(&entity->mGeneralDataComponent->position)) == section)
				entity->mGeneralDataComponent->section = section;
		}
	}
}

void EntityManager::deleteSectionTempEntities(int section)
{
	for (Entity* tempEntity : mEntities[section])
	{
		if (tempEntity->mGeneralDataComponent->tempEntity)
			deleteEntity(tempEntity);
	}
}

std::vector<Entity*>* EntityManager::getEntitiesFromSection(int section)
{
	return &mEntities[section];
}

std::vector<Entity*> EntityManager::updateAndGetEntitiesFromSection(int section)
{
	std::vector<Entity*> returnVector;
	for (std::pair<unsigned int, std::vector<Entity*>> entityTypes : mEntities)
	{
		for (Entity* entity : entityTypes.second)
		{
			if (getSection(&getSectionPair(&entity->mGeneralDataComponent->position)) == section)
			{
				entity->mGeneralDataComponent->section = section;
				returnVector.push_back(entity);
			}
		}
	}

	return returnVector;
}

void EntityManager::refreshSection(unsigned int section)
{
	std::vector<Entity*> tempEntityStorage;
	for (Entity* entity : mEntities[section])
	{
		tempEntityStorage.push_back(entity);
	}

	mEntities[section].clear();

	for (Entity* entity : tempEntityStorage)
	{
		updateEntitySection(entity);
		mEntities[entity->mGeneralDataComponent->section].push_back(entity);
	}
}

void EntityManager::refreshSections()
{
	std::vector<Entity*> tempEntityStorage;
	for (std::pair<unsigned int, std::vector<Entity*>> sectionEntities : mEntities)
	{
		for (Entity* entity : sectionEntities.second)
		{
			tempEntityStorage.push_back(entity);
		}

		sectionEntities.second.clear();
	}

	mEntities.clear();

	for (Entity* entity : tempEntityStorage)
	{
		updateEntitySection(entity);

		if (entity->mGeneralDataComponent->section == 0)
		{
			std::pair<int, int> pos = getSectionPair(&entity->mGeneralDataComponent->position);
			addSection(&pos);
		}

		mEntities[entity->mGeneralDataComponent->section].push_back(entity);
	}
}

Entity * EntityManager::getEntity(unsigned int type, int id)
{
	return mEntities[type][id];
}

Entity * EntityManager::getLastEntity()
{
	return lastEntityCreated;
}

std::vector<Entity*> EntityManager::getEntitiesOfType(unsigned int type, unsigned int section)
{
	if (section == 0)
		section = mCurrentSection;

	std::vector<Entity*> returnVector;

	for (Entity* entity : mEntities[section])
	{
		if(entity->mGeneralDataComponent->type == type)
			returnVector.push_back(entity);
	}

	return returnVector;
}

std::vector<Entity*> EntityManager::getEntitiesFromLayer(std::vector<Entity*>* entities, unsigned int layer)
{
	std::vector<Entity*> layerEntities;
	for (Entity* entity : *entities)
	{
		if (entity->mGeneralDataComponent->layer == layer)
			layerEntities.push_back(entity);
	}

	return layerEntities;
}

void EntityManager::setEntityPosition(Entity * inEntity, Vector2d * pos)
{
	inEntity->mGeneralDataComponent->position = *pos;
}

void EntityManager::updateEntitySection(Entity* inEntity)
{
	if (inEntity->mGeneralDataComponent->section != getSection(getSectionPair(&inEntity->mGeneralDataComponent->position)))
	{
		if (inEntity->mGeneralDataComponent->section != 0)
		{
			eraseEntity(inEntity);
			mEntities[getSection(getSectionPair(&inEntity->mGeneralDataComponent->position))].push_back(inEntity);
		}

		setEntitySection(inEntity->mGeneralDataComponent, getSection(getSectionPair(&inEntity->mGeneralDataComponent->position)));
	}
}

void EntityManager::updateChildren(Entity * inEntity)
{
	for (Entity *child : *inEntity->getChildren())
	{
		child->mGeneralDataComponent->position = inEntity->mGeneralDataComponent->position;
	}
}
