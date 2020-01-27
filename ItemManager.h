#pragma once
#include "ToolComponent.h"
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include "Vector2d.h"

class ItemManager
{
private:
	std::shared_ptr<sf::Texture> m_ItemSet;
	sf::Vector2u m_ItemSize; // Size in pixel units per item sprite
public:
	ItemManager();
	~ItemManager();

	void setItemSet(const std::string& itemSet, sf::Vector2u itemSize);

	void assignToolProperties(ToolComponent* inItem);
	void setItemTexture(ItemComponent* inItem);

private:
	void calculateToolStats(ToolComponent* inItem);
};

