#include "Menu.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

Menu::Menu(int menuType, const std::string * texturePath)
{
	if (menuType > 0 || texturePath != nullptr)
		constructMenu(menuType, texturePath);
}


Menu::~Menu()
{
	for (auto rectangle : mRectangles)
	{
		delete rectangle;
	}
	mRectangles.clear();
}

void Menu::constructMenu(int menuType, const std::string * texturePath)
{
	if (!mTileset.loadFromFile(*texturePath))
		std::cout << "Failed to load the texture from this path: " << texturePath << std::endl;
	else
	{
		mComp.texturePath = *texturePath;

		//Add a background sprite
		mRectangles.push_back(new sf::RectangleShape);

		switch (menuType)
		{
		case CRAFTING_MENU:
			consturctCraftingMenu();
		case INVENTORY_MENU:
			consturctInventoryMenu();
		case ESCAPE_MENU:
			consturctEscapeMenu();
		default:
			break;
		}
	}
}

void Menu::toggleVis(bool button)
{
	if (button && bDraw && !bToggled)
	{
		bDraw = false;
		std::cout << "Menu NOT Visible" << std::endl;
	}
	else if (button && !bDraw && !bToggled)
	{
		bDraw = true;
		std::cout << "Menu Visible" << std::endl;
	}

	if (button)
		bToggled = true;
	else
		bToggled = false;
}

void Menu::draw(sf::RenderTarget & target, Vector2d * playerPos)
{
	if (bDraw)
	{
		setPosition(playerPos);

		for (auto rectangle : mRectangles)
			target.draw(*rectangle);
	}
}

void Menu::consturctCraftingMenu()
{
	// Background
	mRectangles[0]->setSize(sf::Vector2f(100, 50));
	sf::Color newColour;
	newColour.r = 255; newColour.b = 155;  newColour.g = 255; newColour.a = 100;
	mRectangles[0]->setFillColor(newColour);
	mRectangles[0]->setOutlineColor(sf::Color::Black);
	mRectangles[0]->setOutlineThickness(0.5);
	sf::Vector2f backgroundCenter(mRectangles[0]->getSize() * 0.5f);
	mRectangles[0]->setOrigin(backgroundCenter);

	for (int i = 1; i <= mTileset.getSize().x / 16; i++)
	{
		mRectangles.push_back(new sf::RectangleShape);
		mRectangles[i]->setSize(sf::Vector2f(16, 16));
		mRectangles[i]->setTexture(&mTileset);
		mRectangles[i]->setOutlineColor(sf::Color::Black);
		mRectangles[i]->setOutlineThickness(0.5);
		mRectangles[i]->setOrigin(mRectangles[0]->getOrigin());
		mRectangles[i]->setPosition(backgroundCenter + (mRectangles[i]->getSize() * -0.5f));
		mRectangles[i]->setPosition(mRectangles[i]->getPosition().x - (((mTileset.getSize().x + ((((mTileset.getSize().x - 16) / 16.f) * elementSpacing)) - 16) * 0.5f)) + ((16 + elementSpacing) * (i - 1)), mRectangles[i]->getPosition().y + 16);

		int numX = mTileset.getSize().x / mRectangles[i]->getSize().x;
		int numY = mTileset.getSize().y / mRectangles[i]->getSize().y;

		// find its position in the tileset texture
		int left = ((i - 1) % numX) * mRectangles[i]->getSize().x;
		int top = ((i - 1) % numY) * mRectangles[i]->getSize().y;

		// assign the texture
		mRectangles[i]->setTextureRect(sf::IntRect(left, top, mRectangles[i]->getSize().x, mRectangles[i]->getSize().y));
	}
}

void Menu::consturctInventoryMenu()
{
}

void Menu::consturctEscapeMenu()
{
}

void Menu::setPosition(Vector2d * playerPos)
{
	mRectangles[0]->setOrigin(-playerPos->toSf() - (mRectangles[0]->getSize() * -0.5f));

	for (auto rectangle : mRectangles)
		rectangle->setOrigin(mRectangles[0]->getOrigin());
}
