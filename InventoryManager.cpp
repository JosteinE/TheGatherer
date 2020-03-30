#include "InventoryManager.h"
#include "InventoryComponent.h"
#include "Items.h"
#include "TileMap.h"
#include "Vector2d.h"
#include "GeneralDataComponent.h"

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

void InventoryManager::harvestTile(sf::Vector2i mousePos, TileMap * map, GeneralDataComponent* genComp, InventoryComponent * invComp)
{
	if (mousePos.x <= 20 && mousePos.y <= 20 && mousePos.x >= -20 && mousePos.y >= -15)
	{
		Vector2d mouseLoc{ mousePos.x + genComp->position.x, mousePos.y + genComp->position.y };
		if (map->getTileTextureIndex(map->getTileIndex(&mouseLoc)) == 1)
		{
			invComp->numMinerals++;
			std::cout << "Minerals: " << invComp->numMinerals << std::endl;
		}
		else if(map->getTileTextureIndex(map->getTileIndex(&mouseLoc)) == 2)
		{
			invComp->numWood++;
			std::cout << "Wood: " << invComp->numWood << std::endl;
		}

		if(map->getTileTextureIndex(map->getTileIndex(&mouseLoc)) == 0)
			map->setTileTexture(map->getTileIndex(&mouseLoc), 4);
		else
			map->setTileTexture(map->getTileIndex(&mouseLoc), 0);
	}
}

bool InventoryManager::placeTile(sf::Vector2i mousePos, TileMap * map, GeneralDataComponent * genComp, InventoryComponent * invComp, unsigned int itemSelected)
{
	Vector2d mouseLoc{ mousePos.x + genComp->position.x, mousePos.y + genComp->position.y };
	unsigned int currentTileTexture = map->getTileTextureIndex(map->getTileIndex(&mouseLoc));
	if (currentTileTexture == 0 || currentTileTexture == 4)
	{
		switch (itemSelected)
		{
		case 5: // Stone
			if (invComp->numMinerals > 0)
			{
				invComp->numMinerals--;
				map->setTileTexture(map->getTileIndex(&mouseLoc), itemSelected);
			}
			else return false;
			break;
		case 6: // Wood
			if (invComp->numWood > 0)
			{
				invComp->numWood--;
				map->setTileTexture(map->getTileIndex(&mouseLoc), itemSelected);
			}
			else return false;
			break;
		case 7: // Iron
			if (invComp->numMinerals > 10)
			{
				invComp->numMinerals--;
				map->setTileTexture(map->getTileIndex(&mouseLoc), itemSelected);
			}
			else return false;
			break;
		default:
			break;

			return true;
		}

		return true;
	}
}
