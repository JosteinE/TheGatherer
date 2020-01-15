#pragma once
#include <vector>
#include <map>
#include "Entity.h" // Including for the components enum

class EntityManager
{
private:
	std::vector<Entity*> mEntities;
	std::map<unsigned int, std::vector<Entity*>> mLayers; // 0 = background, 1 = player space, 2, foreground
public:
	EntityManager();
	~EntityManager();

	void addNewEntity(int layer = 0, std::vector<int>* comps = nullptr);
	void addComponentToEntity(Entity* inEntity, int comp);
	void addComponentsToEntity(Entity* inEntity, std::vector<int>* comps);

	void setEntityLayer(Entity* inEntity, int layer);
	void removeEntities();

	Entity* getEntity(int id);
	Entity* getLastEntity(); // returns the last added entity
	std::vector<Entity*>* getEntities();
	std::vector<Entity*>* getEntitiesFromLayer(unsigned int layer);
};

