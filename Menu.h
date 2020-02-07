#pragma once
#include "MenuComponent.h"
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

enum MENU_TYPE
{
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
	bool bDraw{ false };
	bool bToggled{ false };

	int elementSpacing = 16;
public:
	Menu(int menuType = -1, const std::string * fontPath = nullptr, const std::string * texturePath = nullptr);
	~Menu();
	void constructMenu(int menuType, const std::string * fontPath, const std::string * texturePath);

	void toggleVis(bool button);

	void draw(sf::RenderTarget& target, Vector2d * playerPos);

private:
	void consturctCraftingMenu();
	void consturctInventoryMenu();
	void consturctEscapeMenu();

	void setPosition(Vector2d * playerPos);
};

