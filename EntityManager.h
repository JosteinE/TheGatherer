#pragma once
#include <vector>
#include <map>
#include "Entity.h" // Including for the components enum
#include <memory>

class EntityManager
{
private:
	// ID Entity
	std::map<unsigned int, std::shared_ptr<Entity>> mEntities;
	// Layer & ID - 0 = background(tiles), 1 = backgroundDetails, 2 = interactable(player space), 3 = foreground, 4 = HUD
	std::map<unsigned int, std::vector<unsigned int>> mLayers;
	std::vector<int> removedIDs;
	Entity* mLastEntityCreated;
public:
	EntityManager();
	~EntityManager();

	void addNewEntity(unsigned int layer = 0, std::vector<int>* comps = nullptr);
	void addComponentToEntity(Entity* inEntity, int comp);
	void addComponentsToEntity(Entity* inEntity, std::vector<int>* comps);

	void setEntityLayer(Entity* inEntity, unsigned int layer);
	void removeEntity(Entity* inEntity);
	void removeEntity(unsigned int inID);
	void removeEntities();

	std::shared_ptr<Entity> getEntity(unsigned int id);
	Entity* getLastEntity(); // returns the last added entity
	std::vector<unsigned int>* getEntitiesFromLayer(unsigned int layer);

private:
	void assignID(std::shared_ptr<Entity> inEntity);
};

