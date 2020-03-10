#include "Menu.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

Menu::Menu()
{
	// TEMP
	const std::string fontPath = "Assets/Fonts/IndieFlower-Regular.ttf";
	const std::string texturePath = "Assets/Textures/ItemSet.png";
	setMenuAssets(&fontPath, &texturePath);
}


Menu::~Menu()
{
	deleteMenuContent();
}

void Menu::setScreenSize(sf::Vector2u* screenSize)
{
	mScreenSize = screenSize;
}

void Menu::constructMenu(int menuType, const std::string * fontPath, const std::string * texturePath)
{
	if(bAssetsLoaded || setMenuAssets(fontPath, texturePath))
	{
		if (menuConstructed != UNDEFINED_MENU)
			deleteMenuContent();

		switch (menuType)
		{
		case CRAFTING_MENU:
			consturctCraftingMenu(); break;
		case INVENTORY_MENU:
			consturctInventoryMenu(); break;
		case ESCAPE_MENU:
			consturctEscapeMenu(); break;
		case MAIN_MENU:
			consturctMainMenu(); break;
		default:
			return;
		}

		menuConstructed = menuType;
	}
	else
		std::cout << "Couldn't construct the menu because of missing assets!" << std::endl;
}

bool Menu::setMenuAssets(const std::string * fontPath, const std::string * texturePath)
{
	if (!mTileset.loadFromFile(*texturePath))
	{
		std::cout << "Failed to load the texture from this path: " << texturePath << std::endl;
		return false;
	}
	else
	{
		mComp.texturePath = *texturePath;

		if (!mFont.loadFromFile(*fontPath))
			std::cout << "Could not load font." << std::endl;
		else
		{
			mComp.fontPath = *fontPath;
			bAssetsLoaded = true;
			return true;
		}
	}
}

void Menu::draw(sf::RenderTarget & target, Vector2d * playerPos)
{
	if(playerPos != nullptr)
		setPosition(playerPos);

	for (auto rectangle : mRectangles)
		target.draw(*rectangle);
	for (auto text : mText)
		target.draw(*text);
}

void Menu::deleteMenuContent()
{
	for (auto rectangle : mRectangles)
		delete rectangle;
	for (auto text : mText)
		delete text;
	mRectangles.clear();
	mText.clear();
	menuConstructed = UNDEFINED_MENU;
}

void Menu::consturctCraftingMenu()
{
	// Background
	mRectangles.push_back(new sf::RectangleShape);
	mRectangles[0]->setSize(sf::Vector2f(100, 50));
	sf::Color newColour{ 255, 255, 155, 100 };
	mRectangles[0]->setFillColor(newColour);
	mRectangles[0]->setOutlineColor(sf::Color::Black);
	mRectangles[0]->setOutlineThickness(0.5);
	sf::Vector2f backgroundCenter(mRectangles[0]->getSize() * 0.5f);
	mRectangles[0]->setOrigin(backgroundCenter);

	// Title
	mText.push_back(new sf::Text);
	mText[0]->setFont(mFont);
	mText[0]->setString("Select what to craft");
	mText[0]->setCharacterSize(100);
	mText[0]->setScale(0.1, 0.1);
	mText[0]->setOrigin(mRectangles[0]->getOrigin());
	mText[0]->setPosition(5, 0);
	mText[0]->setFillColor(sf::Color::Yellow);
	mText[0]->setStyle(sf::Text::Bold);

	// Buttons
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

void Menu::consturctMainMenu()
{
	// Background
	mRectangles.push_back(new sf::RectangleShape);
	mRectangles[0]->setSize(sf::Vector2f(mScreenSize->x, mScreenSize->y));
	sf::Color newColour{ 255, 255, 155, 100 };
	mRectangles[0]->setFillColor(newColour);
	mRectangles[0]->setOutlineColor(sf::Color::Black);
	mRectangles[0]->setOutlineThickness(0.5);
	sf::Vector2f backgroundCenter(mRectangles[0]->getSize() * 0.5f);
	mRectangles[0]->setOrigin(backgroundCenter);
	mRectangles[0]->setPosition(backgroundCenter);

	// Title
	mText.push_back(new sf::Text);
	mText[0]->setFont(mFont);
	mText[0]->setString("The Gatherer");
	mText[0]->setCharacterSize(100);
	mText[0]->setScale(1, 1);
	mText[0]->setOrigin(backgroundCenter);
	mText[0]->setPosition(sf::Vector2f{backgroundCenter.x + mScreenSize->x * 0.33f, backgroundCenter.y * 1.5f});
	mText[0]->setFillColor(sf::Color::Black);
	mText[0]->setStyle(sf::Text::Bold);

	// Buttons
	float xDistance = mScreenSize->x / 3 ;

	for (int i = 1; i <= 3; i++)
	{
		mRectangles.push_back(new sf::RectangleShape);
		mRectangles[i]->setSize(sf::Vector2f(300, 100));
		mRectangles[i]->setFillColor(newColour);
		mRectangles[i]->setOutlineColor(sf::Color::Black);
		mRectangles[i]->setOutlineThickness(1.f);
		mRectangles[i]->setOrigin(backgroundCenter);

		sf::Vector2f newPosition = getRectToCenter(&mRectangles[i]->getSize());
		newPosition.x += xDistance * (i - 2);
		newPosition.y += 300.f;
		mRectangles[i]->setPosition(newPosition);

		mText.push_back(new sf::Text);
		mText[i]->setFont(mFont);
		mText[i]->setCharacterSize(100);
		mText[i]->setScale(0.5f, 0.5f);
		mText[i]->setFillColor(sf::Color::Black);
		mText[i]->setStyle(sf::Text::Bold);
		mText[i]->setOrigin(newPosition);
		newPosition.x += 300 * (i - 2);
		newPosition.y *= 1.12f;
		mText[i]->setPosition(newPosition);
	}

	mText[1]->setString("New Game");
	mText[2]->setString("Load Game");
	mText[3]->setString("Options");
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

sf::Vector2f Menu::getRectToCenter(const sf::Vector2f * rectangleSize)
{
	return sf::Vector2f(mScreenSize->x - rectangleSize->x * 0.5f, mScreenSize->y - rectangleSize->y * 0.5f);
}
