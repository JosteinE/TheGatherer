#include "ItemManager.h"
#include "Items.h"


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

void ItemManager::setItemSet(const std::string & itemSet, sf::Vector2u itemSize)
{
	sf::Texture set;
	if (!set.loadFromFile(itemSet))
	{
		std::cout << "Failed to load the item set" << std::endl;
		return;
	}
	m_ItemSet = std::make_shared<sf::Texture>(set);
	m_ItemSize = itemSize;
}

void ItemManager::assignToolProperties(ToolComponent * inItem)
{
	if (inItem != nullptr && inItem->itemID != NULL_ID)
	{
		calculateToolStats(inItem);
		setItemTexture(inItem);
	}
}

void ItemManager::calculateToolStats(ToolComponent * inItem)
{
	switch (inItem->itemID)
	{	// This is pretty silly atm, I know, but I assume I'll have to fine tune these later!
		case AXE_ID:
			inItem->toolPower = inItem->toolTier;
			inItem->toolSpeed = inItem->toolTier;
			inItem->toolReach = inItem->toolTier;
		case PICKAXE_ID:
			inItem->toolPower = inItem->toolTier;
			inItem->toolSpeed = inItem->toolTier;
			inItem->toolReach = inItem->toolTier;
		case SWORD_ID:
			inItem->toolPower = inItem->toolTier;
			inItem->toolSpeed = inItem->toolTier;
			inItem->toolReach = inItem->toolTier;

		default:
			break;
	}
}

void ItemManager::setItemTexture(ItemComponent * inItem)
{
	// get the current tile number
	int itemNumber = inItem->itemID;

	// find its position in the tileset texture
	int tu = itemNumber % (m_ItemSet->getSize().x / m_ItemSize.x);

	// assign the texture
	inItem->mSprite->setTexture(*m_ItemSet.get());

	// get a pointer to the current item's rectangle
	sf::IntRect itemTexture(tu, 0, m_ItemSize.x, m_ItemSize.y);
	inItem->mSprite->setTextureRect(itemTexture);
}
