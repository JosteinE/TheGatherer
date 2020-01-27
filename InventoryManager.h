#pragma once
#include "InventoryComponent.h"
#include "ToolComponent.h"

struct InventoryComponent;
struct ToolComponent;
struct ItemComponent;

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
};

