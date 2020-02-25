#pragma once
#include <unordered_map>
#include <vector>
#include <map>
#include "Entity.h" // Including for the components enum
#include "Vector2d.h"
#include <memory>

enum ENTITY_TYPE 
{
	UNDEFINED_ENTITY,
	ITEM_ENTITY,
	PLAYER_ENTITY,
	NPC_ENTITY,
	OTHER_ENTITY
};

class ItemManager;

class EntityManager
{
private:
	Vector2d sectionSize{ 320, 320 }; // 20 x 16
	std::map<std::pair<int, int>, int> mSections;
	std::vector<Entity*> mCurrentEntities;
	int mCurrentSection = 0;


	std::unordered_map<unsigned int, std::vector<Entity*>> mEntities; // Type and enities of that type
	std::vector<Entity*> mLayers[4]; // 0 = background(tiles), 1 = backgroundDetails, 2 = interactable(player space), 3 = foreground
	Entity* lastEntityCreated{ nullptr };
public:
	EntityManager();
	~EntityManager();

	void createNewEntity(unsigned int type, int layer = 0, bool addGeneralComponent = true);
	void createNewEntity(unsigned int type, int layer = 0, std::vector<int>* comps = nullptr);
	void createNewItemEntity(ItemManager* itemM, unsigned int itemID, bool isTool, unsigned int itemTier = 0);
	void addComponentToEntity(Entity* inEntity, int comp);
	void addComponentsToEntity(Entity* inEntity, std::vector<int>* comps);

	void setEntityLayer(Entity* inEntity, int layer);

	void deleteEntity(unsigned int type, Entity* inEntity, bool deleteChildren = false);
	void deleteEntities();
	void deleteEntities(std::vector<Entity*> inEntities, bool deleteChildren = false);

	Entity* getEntity(unsigned int type, int id);
	Entity* getLastEntity(); // returns the last added entity
	std::vector<Entity*>* getEntities(unsigned int type);
	std::vector<Entity*>* getEntitiesFromLayer(unsigned int layer);

	void updateChildren(Entity* inEntity);

	std::vector<Entity*>* getRenderSection(Vector2d* position);

private:
	void setEntitySection(Entity* inEntity, int section);

	int getSection(std::pair<int, int>* position);
	std::pair<int, int> getSectionPair(Vector2d* position);
	void addSection(std::pair<int, int>* position);
	void setCurrentSection(std::pair<int, int>* position);
	void updateSection(std::pair<int, int>* position);
	std::vector<Entity*> getEntitiesFromSection(int section);
};

