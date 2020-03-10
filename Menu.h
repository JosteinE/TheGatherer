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
	INVENTORY_MENU,
	ESCAPE_MENU,
};

class RenderTarget;

class Menu
{
private:
	std::vector<sf::RectangleShape*> mRectangles;
	std::vector<sf::Text*> mText;
	sf::Texture mTileset;
	MenuComponent mComp;
	sf::Font mFont;
	bool bToggled{ false };
	bool bAssetsLoaded{ false };

	int elementSpacing = 16;
public:
	int menuConstructed = UNDEFINED_MENU;

	Menu();
	~Menu();
	void constructMenu(int menuType, const std::string * fontPath = nullptr, const std::string * texturePath = nullptr);
	bool setMenuAssets(const std::string * fontPath, const std::string * texturePath);

	void toggleVis(bool button);

	void draw(sf::RenderTarget& target, Vector2d * playerPos = nullptr);

	void deleteMenuContent();

private:
	void consturctCraftingMenu();
	void consturctInventoryMenu();
	void consturctEscapeMenu();
	void consturctMainMenu();

	void setPosition(Vector2d * playerPos);
};

