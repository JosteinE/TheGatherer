#pragma once
#include <unordered_map>
#include <vector>
#include <map>
#include "Entity.h" // Including for the components enum

enum ENTITY_TYPE 
{
	NONE,
	ITEM,
	CHARACTER,
	OTHER
};

class ItemManager;

class EntityManager
{
private:
	std::unordered_map<unsigned int, std::vector<Entity*>> mEntities; // Make use of the ENTITY_TYPE enum!
	//std::vector<Entity*> mEntities;
	std::vector<Entity*> mLayers[4]; // 0 = background(tiles), 1 = backgroundDetails, 2 = interactable(player space), 3 = foreground
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

	Entity* getEntity(int id);
	Entity* getLastEntity(); // returns the last added entity
	std::vector<Entity*>* getEntities();
	std::vector<Entity*>* getEntitiesFromLayer(unsigned int layer);

	void updateChildren(Entity* inEntity);
};

