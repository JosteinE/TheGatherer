#include "Menu.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

Menu::Menu(int menuType, const std::string * fontPath, const std::string * texturePath)
{
	if (menuType > 0 && fontPath != nullptr && texturePath != nullptr)
		constructMenu(menuType, fontPath, texturePath);
}


Menu::~Menu()
{
	for (auto rectangle : mRectangles)
		delete rectangle;
	for (auto text : mText)
		delete text;
	mRectangles.clear();
	mText.clear();
}

void Menu::constructMenu(int menuType, const std::string * fontPath, const std::string * texturePath)
{
	if (!mTileset.loadFromFile(*texturePath))
		std::cout << "Failed to load the texture from this path: " << texturePath << std::endl;
	else
	{
		mComp.texturePath = *texturePath;

		if (!mFont.loadFromFile(*fontPath))
			std::cout << "Could not load font." << std::endl;
		else
			mComp.fontPath = *fontPath;

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
		for (auto text : mText)
			target.draw(*text);
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

	// Title
	mText.push_back(new sf::Text);
	mText[0]->setFont(mFont);
	mText[0]->setString("Select at item to craft");
	mText[0]->setCharacterSize(100);
	mText[0]->setScale(0.1, 0.1);
	mText[0]->setOrigin(mRectangles[0]->getOrigin());
	mText[0]->setPosition(0, 0);
	mText[0]->setFillColor(sf::Color::Yellow);
	mText[0]->setStyle(sf::Text::Bold);

	for (int i = 1; i <= mTileset.getSize().x / 16; i++)
	{
		mRectangles.push_back(new sf::RectangleShape);
		mRectangles[i]->setSize(sf::Vector2f(16, 16));
		mRectangles[i]->setTexture(&mTileset);
		mRectangles[i]->setOutlineColor(sf::Color::Black);
		mRectangles[i]->setOutlineThickness(0.5);
		mRectangles[i]->setOrigin(mRectangles[0]->getOrigin());
		mRectangles[i]->setPosition(backgroundCenter - (mRectangles[i]->getSize() * 0.5f));
		sf::Vector2f newPosition(mRectangles[i]->getPosition().x - (((mTileset.getSize().x + ((((mTileset.getSize().x - 16) / 16.f) * elementSpacing)) - 16) * 0.5f)) + ((16 + elementSpacing) * (i - 1)), mRectangles[i]->getPosition().y);
		mRectangles[i]->setPosition(newPosition);

		// Add the text underneath
		mText.push_back(new sf::Text);
		mText[i]->setFont(mFont);
		mText[i]->setCharacterSize(100);
		mText[i]->setScale(0.1, 0.1);
		mText[i]->setPosition(newPosition.x, newPosition.y + mRectangles[i]->getSize().y);
		mText[i]->setOrigin(mRectangles[0]->getOrigin());
		mText[i]->setFillColor(sf::Color::Yellow);
		mText[i]->setStyle(sf::Text::Bold);

		// find its position in the tileset texture
		int left = ((i - 1) % static_cast<int>(mTileset.getSize().x / mRectangles[i]->getSize().x)) * mRectangles[i]->getSize().x;
		int top = ((i - 1) % static_cast<int>(mTileset.getSize().y / mRectangles[i]->getSize().y)) * mRectangles[i]->getSize().y;

		// assign the texture
		mRectangles[i]->setTextureRect(sf::IntRect(left, top, mRectangles[i]->getSize().x, mRectangles[i]->getSize().y));
	}

	mText[1]->setString("Gear");
	mText[2]->setString("Tool");
	mText[3]->setString("Block");
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
	for (sf::Text* text : mText)
	{
		text->setOrigin(mRectangles[0]->getOrigin().x * (1 / text->getScale().x),
						mRectangles[0]->getOrigin().y * (1 / text->getScale().y));
	}
}
