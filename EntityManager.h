#pragma once
#include <unordered_map>
#include <vector>
#include <map>
#include "Entity.h" // Including for the components enum
#include "Vector2d.h"
#include <memory>
#include "SpawnerComponent.h"

enum ENTITY_TYPE 
{
	UNDEFINED_ENTITY,
	ITEM_ENTITY,
	PLAYER_ENTITY,
	NPC_ENTITY,
	OTHER_ENTITY
};

class ItemManager;

// - Spawn Entities from file once the section is entered
// - remove mLayers
// - turn mEntities into std::vector
// - +mSectionEntities map<int, std::Vector>

class EntitySpawner;
struct GeneralDataComponent;

class EntityManager
{
private:
	// BELONGS IN FILE?
	std::unordered_map<unsigned int, SpawnerComponent*> entitySpawnerComps; //Section & component
	//

	Vector2d sectionSize{ 320, 320 }; // 20 x 16
	std::map<std::pair<int, int>, int> mSections;
	int mCurrentSection = 0;

	std::vector<Entity*> mTempEntities; // Only to be cleared and filled upon entering a new section
	std::unordered_map<unsigned int, std::vector<Entity*>> mEntities; // Section & Entities
	//std::vector<Entity*> mLayers[4]; // 0 = background(tiles), 1 = backgroundDetails, 2 = interactable(player space), 3 = foreground
	Entity* lastEntityCreated{ nullptr };
public:
	EntityManager(Vector2d* inSectionSize);
	~EntityManager();

	void createNewEntity(unsigned int type, int layer = 0, bool addGeneralComponent = true, bool isTemp = false);
	void createNewEntity(unsigned int type, int layer = 0, std::vector<int>* comps = nullptr, bool isTemp = false);
	void createNewItemEntity(ItemManager* itemM, unsigned int itemID, bool isTool, unsigned int itemTier = 0);
	void addComponentToEntity(Entity* inEntity, int comp);
	void addComponentsToEntity(Entity* inEntity, std::vector<int>* comps);

	void setEntityLayer(GeneralDataComponent* inEntityComp, int layer);

	bool eraseEntity(Entity* inEntity);
	void deleteEntity(Entity* inEntity, bool deleteChildren = false);
	void deleteEntities();
	void deleteEntities(std::vector<Entity*> inEntities, bool deleteChildren = false);

	Entity* getEntity(unsigned int type, int id);
	Entity* getLastEntity(); // returns the last added entity
	std::vector<Entity*> getEntities();
	std::vector<Entity*> getEntitiesOfType(unsigned int type, unsigned int section = 0);
	std::vector<Entity*> getEntitiesFromLayer(std::vector<Entity*>* entities, unsigned int layer);
	std::vector<Entity*>* getEntitiesFromSection(int section);

	void setEntityPosition(Entity* inEntity, Vector2d * pos);
	void updateEntitySection(Entity* inEntity, bool eraseFromPreviousSection = true);

	void refreshSection(unsigned int section);
	void refreshSections();

	void updateChildren(Entity* inEntity);
	void importSpawners(std::vector<SpawnerComponent*> inSpawnerComps);
	std::vector<Entity*>* getRenderSection(Vector2d* position, EntitySpawner* spawner);
	int getCurrentSectionIndex();
private:
	void setEntitySection(Entity * inEntity, int section, bool eraseFromPreviousSection = true);

	int getSection(std::pair<int, int>* position);
	int getSection(std::pair<int, int> position);
	std::pair<int, int> getSectionPair(Vector2d* position);
	void addSection(std::pair<int, int>* position);
	void setCurrentSection(int section);
	std::vector<Entity*> locateSectionEntities(int section);
	void updateSection(int section);
	void deleteSectionTempEntities(int section);
	std::vector<Entity*> updateAndGetEntitiesFromSection(int section);
	bool checkSectionExistence(std::pair<int, int> position);

	Vector2d getSectionCenter(int section);
	bool sectionHasSpawner(int section);
	void spawnTempEntities(EntitySpawner* spawner, int section);
};

