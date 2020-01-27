#pragma once
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include "Vector2d.h"

struct SpriteComponent;
struct ToolComponent;
struct ItemComponent;

class ItemManager
{
private:
	std::shared_ptr<sf::Texture> m_ItemSet;
	sf::Vector2u m_ItemSize; // Size in pixel units per item sprite
public:
	ItemManager();
	~ItemManager();

	void setItemSetAndSize(std::shared_ptr<sf::Texture> itemSet, sf::Vector2u itemSize);

	void assignToolProperties(ToolComponent* inItem, SpriteComponent* inSprite = nullptr);
	void setItemTexture(ItemComponent* inItem, SpriteComponent* inSprite);

private:
	void calculateToolStats(ToolComponent* inItem);
};

