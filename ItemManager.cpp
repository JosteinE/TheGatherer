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
	int left = itemNumber % (m_ItemSet->getSize().x / m_ItemSize.x);
	int top = itemNumber % (m_ItemSet->getSize().y / m_ItemSize.y);

	// assign the texture
	inItemSprite->mSprite->setTexture(*m_ItemSet.get());
	inItemSprite->mSprite->setTextureRect(sf::IntRect(left * m_ItemSize.x, top * m_ItemSize.y, m_ItemSize.x, m_ItemSize.y));
	inItemSprite->mSprite->setOrigin(sf::Vector2f(m_ItemSize.x * 0.5f, m_ItemSize.y * 0.5f));

	std::cout << "setSizeX: " << m_ItemSet->getSize().x << std::endl;
	std::cout << "setSizeY: " << m_ItemSet->getSize().y << std::endl;
	std::cout << "left: " << left << std::endl;
	std::cout << "top: " << top << std::endl;
	std::cout << "origin: (" << inItemSprite->mSprite->getOrigin().x << ", " << inItemSprite->mSprite->getOrigin().y << ")" << std::endl;
}
