#include "EntityManager.h"
#include <iostream>
#include "GeneralDataComponent.h"
#include "ToolComponent.h"
#include "ItemManager.h"
#include "SpriteComponent.h"

#include "EntitySpawner.h"

#include <algorithm>

EntityManager::EntityManager(Vector2d* inSectionSize)
{
	sectionSize = *inSectionSize;
}


EntityManager::~EntityManager()
{
	deleteEntities();

	for (std::pair<int, SpawnerComponent*> spawnerCompPair : entitySpawnerComps)
		delete spawnerCompPair.second;
	entitySpawnerComps.clear();
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
		inEntityComp->layer = layer;
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
			int numChildren = inEntity->getChildren()->size();
			for (int i = 0; i < numChildren; i++)
			{
				deleteEntity((*inEntity->getChildren())[0], true);
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
			delete entity;
		}
		entityType.second.clear();
		entityType.second.resize(0);
	}
	
	mEntities.clear();
}

void EntityManager::deleteEntities(std::vector<Entity*> inEntities, bool deleteChildren)
{
	for (Entity* entity : inEntities)
		deleteEntity(entity, deleteChildren);
}

std::vector<Entity*>* EntityManager::getRenderSection(Vector2d * position, EntitySpawner* spawner)
{
	std::pair<int, int> pos = getSectionPair(position);

	if (!checkSectionExistence(pos))
		addSection(&pos);

	int section = getSection(&pos);
	
	if (mCurrentSection != section)
	{
		// Update last section before leaving it
		if(mCurrentSection != 0)
			deleteSectionTempEntities(mCurrentSection);
		refreshSection(mCurrentSection);

		// Prepare the new section
		if (sectionHasSpawner(section))
		{
			spawnTempEntities(spawner, section);
		}
		setCurrentSection(section);
		std::cout << "Current section: " << mCurrentSection << std::endl;
		std::cout << "Current section size: " << mEntities[mCurrentSection].size() << std::endl;
	}

	return &mEntities[mCurrentSection];
}

int EntityManager::getCurrentSectionIndex()
{
	return mCurrentSection;
}

void EntityManager::setEntitySection(Entity * inEntity, int section, bool eraseFromPreviousSection)
{
	if(eraseFromPreviousSection)
		eraseEntity(inEntity);
	
	inEntity->mGeneralDataComponent->section = section;
	mEntities[section].push_back(inEntity);
	for (Entity* child : *inEntity->getChildren())
		setEntitySection(child, section, eraseFromPreviousSection);
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

std::vector<Entity*> EntityManager::locateSectionEntities(int section)
{
	std::vector<Entity*> returnVector;
	for (std::pair<unsigned int, std::vector<Entity*>> entityTypes : mEntities)
	{
		for (Entity* entity : entityTypes.second)
		{
			if (getSection(&getSectionPair(&entity->mGeneralDataComponent->position)) == section)
				returnVector.push_back(entity);
		}
	}
	return returnVector;
}

void EntityManager::updateSection(int section)
{
	for (Entity* entity : locateSectionEntities(section))
	{
		setEntitySection(entity, section, true);
	}
}

void EntityManager::deleteSectionTempEntities(int section)
{
	int counter = 0;
	int sectionSize = mEntities[section].size();
	for (int i = 0, x = 0; i < sectionSize; i++)
	{
		if (mEntities[section][x]->mGeneralDataComponent->tempEntity)
		{
			deleteEntity(mEntities[section][x], false);
			counter++;
		}
		else
			x++;
	}
	std::cout << counter << " temp entities were deleted" << std::endl;
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

bool EntityManager::checkSectionExistence(std::pair<int, int> position)
{
	if (getSection(&position) != 0)
		return true;
	else
		return false;
}

Vector2d EntityManager::getSectionCenter(int section)
{
	for (std::pair<std::pair<int, int>, int> sections : mSections)
	{
		if (sections.second == section)
		{
			return Vector2d{ sections.first.first * sectionSize.x + (sectionSize.x * 0.5f), sections.first.second * sectionSize.y + (sectionSize.y * 0.5f) };
		}
	}
	return Vector2d{ 0.f, 0.f };
}

bool EntityManager::sectionHasSpawner(int section)
{
	for (std::pair<int, SpawnerComponent*> spawnerCompPair : entitySpawnerComps)
	{
		if (spawnerCompPair.first == section)
			return true;
	}

	return false;
}

void EntityManager::spawnTempEntities(EntitySpawner * spawner, int section)
{
	if (sectionHasSpawner(section))
	{
		SpawnerComponent* spawnerComp = entitySpawnerComps[section];
		if (spawnerComp->spawnPoint.x == 0 && spawnerComp->spawnPoint.y == 0)
			spawnerComp->spawnPoint = getSectionCenter(section);

		Vector2d spawnAreaMin{ spawnerComp->spawnPoint.x - spawnerComp->npcMaxRange, spawnerComp->spawnPoint.y - spawnerComp->npcMaxRange };
		Vector2d spawnAreaMax{ spawnerComp->spawnPoint.x + spawnerComp->npcMaxRange, spawnerComp->spawnPoint.y + spawnerComp->npcMaxRange };
		spawner->SpawnDefaultNPC(&spawnAreaMin, &spawnAreaMax, spawnerComp->numToSpawn);
	}
}

void EntityManager::refreshSection(unsigned int section)
{
	for (Entity* entity : mEntities[section])
	{
		updateEntitySection(entity, true);
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
	mSections.clear();

	std::pair<int, int> pos;
	for (Entity* entity : tempEntityStorage)
	{
		pos = getSectionPair(&entity->mGeneralDataComponent->position);
		if (!checkSectionExistence(pos))
			addSection(&pos);

		setEntitySection(entity, getSection(&pos), false);
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

std::vector<Entity*> EntityManager::getEntities()
{
	std::vector<Entity*> entities;
	for (std::pair<unsigned int, std::vector<Entity*>> entitySections : mEntities)
	{
		for (Entity* entity : entitySections.second)
			entities.push_back(entity);
	}
	return entities;
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

void EntityManager::updateEntitySection(Entity* inEntity, bool eraseFromPreviousSection)
{
	if (!checkSectionExistence(getSectionPair(&inEntity->mGeneralDataComponent->position)))
		addSection(&getSectionPair(&inEntity->mGeneralDataComponent->position));

	setEntitySection(inEntity, getSection(getSectionPair(&inEntity->mGeneralDataComponent->position)), eraseFromPreviousSection);
}

void EntityManager::updateChildren(Entity * inEntity)
{
	for (Entity *child : *inEntity->getChildren())
	{
		child->mGeneralDataComponent->position = inEntity->mGeneralDataComponent->position;
		child->mGeneralDataComponent->section = inEntity->mGeneralDataComponent->section;
		updateChildren(child);
	}
}

void EntityManager::importSpawners(std::vector<SpawnerComponent*> inSpawnerComps)
{
	std::cout << "numSpawners: " << inSpawnerComps.size() << std::endl;
	std::cout << "spawnerSections: ";
	for (SpawnerComponent* spawnerComp : inSpawnerComps)
	{
		std::cout << spawnerComp->section << ", ";
		entitySpawnerComps[spawnerComp->section] = spawnerComp;
	}
	std::cout << std::endl;
}
