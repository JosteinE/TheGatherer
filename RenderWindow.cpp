#include "RenderWindow.h"
#include "Entity.h"
#include "ComponentsHeader.h"
#include "Vector2d.h"


RenderWindow::RenderWindow()
{
	//Window
	mWindow = new sf::RenderWindow(sf::VideoMode(1440, 900), "The Gatherer");
}

RenderWindow::~RenderWindow()
{
	for (auto tile : mTiles)
	{
		delete tile;
	}
	mTiles.clear();
	delete mPlayer;
	delete mWindow;
}

void RenderWindow::init()
{
	// Build player pov
	mWindowCenter = sf::Vector2f(mWindow->getSize().x * 0.5f, mWindow->getSize().y * 0.5f);
	playerView.setSize(sf::Vector2f(mWindow->getSize().x * (viewSize * 0.01f), mWindow->getSize().y * (viewSize * 0.01f)));
	playerView.setCenter(mWindowCenter);
	mWindow->setView(playerView);

	// Entities
	mPlayer = new Entity();
	mPlayer->addComponent(ANIMATION_COMPONENT);
	mPlayer->addComponent(COLLISION_COMPONENT);
	mPlayer->addComponent(COMBAT_COMPONENT);
	mPlayer->addComponent(GENERALDATA_COMPONENT);
	mPlayer->addComponent(INPUT_COMPONENT);
	mPlayer->addComponent(INVENTORY_COMPONENT);
	mPlayer->addComponent(MOVEMENT_COMPONENT);
	mPlayer->addComponent(CIRCLESHAPE_COMPONENT);
	mPlayer->mCircleShapeComponent->mShape = new sf::CircleShape(10.f);
	mPlayer->mCircleShapeComponent->mShape->setFillColor(sf::Color::Blue);
	mPlayer->mCircleShapeComponent->mShape->setPosition(mWindowCenter);

	//Map
	sf::Vector2f tileSize(75.f, 75.f);
	sf::Vector2u tileSetSize(50, 50);
	sf::Vector2u tileSpacing(2, 2);

	sf::RectangleShape* tile{ nullptr };
	for (int x = (tileSetSize.x * -0.5f); x < (tileSetSize.x * 0.5f); x++)
	{
		for (int y = (tileSetSize.y * -0.5f); y < (tileSetSize.y * 0.5f); y++)
		{
			tile = new sf::RectangleShape(tileSize);
			tile->setFillColor(sf::Color::Green);
			tile->setPosition(sf::Vector2f(mWindowCenter.x + (tile->getSize().x * x * tileSpacing.x), mWindowCenter.y + (tile->getSize().y * y * tileSpacing.y)));
			mTiles.push_back(tile);
		}
	}
}

void RenderWindow::tick(float deltaTime)
{
	// Register input
	mInputManager.manageInput(mPlayer->mInputComponent);

	// Move and update the player character
	mMovementManager.moveByInput(&mPlayer->mGeneralDataComponent->position, mPlayer->mMovementComponent, mPlayer->mInputComponent, deltaTime);
	mShapeManager.updateShapePosition(mPlayer->mCircleShapeComponent, &mPlayer->mGeneralDataComponent->position);
	
	// Update the camera
	playerView.setCenter(mPlayer->mGeneralDataComponent->position.toSf());
	mWindow->setView(playerView);

	// Draw calls
	for (auto tile : mTiles)
	{
		mWindow->draw(*tile);
	}

	mWindow->draw(*mPlayer->mCircleShapeComponent->mShape);

	mWindow->display();
}
