#include "InventoryManager.h"
#include "InventoryComponent.h"
#include "Items.h"

InventoryManager::InventoryManager()
{
}


InventoryManager::~InventoryManager()
{
}

void InventoryManager::init(InventoryComponent* inventoryComp)
{
	inventoryComp->itemBar[0].itemID = SWORD_ID;
	inventoryComp->itemBar[0].toolTier = 1;
	inventoryComp->itemBar[1].itemID = PICKAXE_ID;
	inventoryComp->itemBar[1].toolTier = 1;
	inventoryComp->itemBar[2].itemID = AXE_ID;
	inventoryComp->itemBar[2].toolTier = 1;
	inventoryComp->currentBarSlot = 0;

	m_inventory = inventoryComp;
}

void InventoryManager::setCurrentBarSlot(unsigned int slot)
{
	if(slot < 3)
		m_inventory->currentBarSlot = slot;
}

ToolComponent * InventoryManager::getCurrentBarSlot()
{
	return &m_inventory->itemBar[m_inventory->currentBarSlot];
}

void InventoryManager::addToInventory(ItemComponent * inItem)
{
}
