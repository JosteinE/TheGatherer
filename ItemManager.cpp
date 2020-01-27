#include "ItemManager.h"
#include "Items.h"
#include "SpriteComponent.h"
#include "ToolComponent.h"

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

void ItemManager::setItemSetAndSize(std::shared_ptr<sf::Texture> itemSet, sf::Vector2u itemSize)
{
	m_ItemSet = itemSet;
	m_ItemSize = itemSize;
}

void ItemManager::assignToolProperties(ToolComponent * inItem, SpriteComponent * inSprite)
{
	if (inItem != nullptr && inItem->itemID != NULL_ID)
	{
		calculateToolStats(inItem);

		if(inSprite != nullptr)
			setItemTexture(inItem, inSprite);
	}
}

void ItemManager::calculateToolStats(ToolComponent * inItem)
{
	switch (inItem->itemID)
	{
		case AXE_ID:
			inItem->toolPower = inItem->toolTier * AXE_POWER;
			inItem->toolSpeed = inItem->toolTier * AXE_SPEED;
		case PICKAXE_ID:
			inItem->toolPower = inItem->toolTier * PICKAXE_POWER;
			inItem->toolSpeed = inItem->toolTier * PICKAXE_SPEED;
		case SWORD_ID:
			inItem->toolPower = inItem->toolTier * SWORD_POWER;
			inItem->toolSpeed = inItem->toolTier * SWORD_SPEED;
		default:
			break;
	}
}

void ItemManager::setItemTexture(ItemComponent* inItem, SpriteComponent* inItemSprite)
{
	// get the current tile number
	int itemNumber = inItem->itemID - 3; // - 3 for testing!!!

	// find its position in the tileset texture
	int left = (itemNumber % (m_ItemSet->getSize().x / m_ItemSize.x)) * m_ItemSize.x;
	int top = (itemNumber % (m_ItemSet->getSize().y / m_ItemSize.y)) *  m_ItemSize.y;

	// assign the texture
	inItemSprite->mSprite->setTexture(*m_ItemSet.get());
	inItemSprite->mSprite->setTextureRect(sf::IntRect(left, top, m_ItemSize.x, m_ItemSize.y));
	inItemSprite->mSprite->setOrigin(sf::Vector2f(m_ItemSize.x * 0.5f, m_ItemSize.y * 0.5f));
}
