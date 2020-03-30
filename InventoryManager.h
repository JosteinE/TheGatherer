#pragma once
#include "InventoryComponent.h"
#include "ToolComponent.h"
#include <SFML/System/Vector2.hpp>

struct GeneralDataComponent;
struct InventoryComponent;
struct ToolComponent;
struct ItemComponent;
class TileMap;

class InventoryManager
{
private:
	InventoryComponent* m_inventory{ nullptr };

public:
	InventoryManager();
	~InventoryManager();
	
	void init(InventoryComponent* inventoryComp);

	void setCurrentBarSlot(unsigned int slot);
	ToolComponent* getCurrentBarSlot();

	void addToInventory(ItemComponent* inItem);
	void harvestTile(sf::Vector2i mousePos, TileMap* map, GeneralDataComponent* genComp, InventoryComponent* invComp);
	bool placeTile(sf::Vector2i mousePos, TileMap* map, GeneralDataComponent* genComp, InventoryComponent* invComp, unsigned int itemSelected);
};

