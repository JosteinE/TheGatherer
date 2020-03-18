#pragma once
#include "MenuComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

enum MENU_TYPE
{
	UNDEFINED_MENU,
	MAIN_MENU,
	CRAFTING_MENU,
	CRAFTING_MENU_GEAR,
	CRAFTING_MENU_TOOL,
	CRAFTING_MENU_BLOCK,
	INVENTORY_MENU,
	ESCAPE_MENU,
};

class RenderTarget;

class Menu
{
private:
	sf::Vector2u* mScreenSize;
	std::vector<sf::RectangleShape*> mRectangles;
	std::vector<unsigned int> mButtonIndices;
	std::vector<sf::Text*> mText;
	sf::Texture mTileset;
	MenuComponent mComp;
	sf::Font mFont;
	bool bAssetsLoaded{ false };

public:
	int menuConstructed = UNDEFINED_MENU;
	unsigned int mCurrentButton = 0;

	Menu();
	~Menu();

	void setScreenSize(sf::Vector2u* screenSize);

	void constructMenu(int menuType, const std::string * fontPath = nullptr, const std::string * texturePath = nullptr);
	bool setMenuAssets(const std::string * fontPath, const std::string * texturePath);

	void nextButton(bool positiveDirection);

	void draw(sf::RenderTarget& target, Vector2d * playerPos = nullptr);

	void deleteMenuContent();

private:
	void consturctCraftingMenu();
	void consturctCraftingMenuBase();
	void consturctCraftingMenuGear();
	void consturctCraftingMenuTool();
	void consturctCraftingMenuBlock();


	void consturctInventoryMenu();
	void consturctEscapeMenu();
	void consturctMainMenu();

	void setPosition(Vector2d * playerPos);
	sf::Vector2f getRectToCenter(const sf::Vector2f * rectangleSize);

	void setCurrentButton(unsigned int buttonIndex);
	void revertButton(unsigned int buttonIndex);
};

