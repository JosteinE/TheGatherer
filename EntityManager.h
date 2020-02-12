#pragma once
#include <vector>
#include <map>
#include "Entity.h" // Including for the components enum

class ItemManager;

class EntityManager
{
private:
	std::vector<Entity*> mEntities;
	std::vector<Entity*> mLayers[4]; // 0 = background(tiles), 1 = backgroundDetails, 2 = interactable(player space), 3 = foreground
public:
	EntityManager();
	~EntityManager();

	void createNewEntity(int layer = 0, bool addGeneralComponent = true);
	void createNewEntity(int layer = 0, std::vector<int>* comps = nullptr);
	void createNewItemEntity(ItemManager* itemM, unsigned int itemID, bool isTool, unsigned int itemTier = 0);
	void addComponentToEntity(Entity* inEntity, int comp);
	void addComponentsToEntity(Entity* inEntity, std::vector<int>* comps);

	void setEntityLayer(Entity* inEntity, int layer);

	void deleteEntity(Entity* inEntity, bool deleteChildren = false);
	void deleteEntities();
	void deleteEntities(std::vector<Entity*> inEntities, bool deleteChildren = false);

	Entity* getEntity(int id);
	Entity* getLastEntity(); // returns the last added entity
	std::vector<Entity*>* getEntities();
	std::vector<Entity*>* getEntitiesFromLayer(unsigned int layer);

	void updateChildren(Entity* inEntity);
};

