#include "RenderWindow.h"
#include "Entity.h"

// Components
#include "GeneralDataComponent.h"
#include "CircleShapeComponent.h"
#include "RectangleShapeComponent.h"

RenderWindow::RenderWindow()
{
}

RenderWindow::~RenderWindow()
{
	delete mPlayer;
}

void RenderWindow::init(sf::Vector2f windowCenter)
{
	mWindowCenter = windowCenter;
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
	mPlayer->mCircleShapeComponent->mShape->setPosition(windowCenter);

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
			tile->setPosition(sf::Vector2f(windowCenter.x + (tile->getSize().x * x * tileSpacing.x), windowCenter.y + (tile->getSize().y * y * tileSpacing.y)));
			mTiles.push_back(tile);
		}
	}
}

void RenderWindow::tick(float deltaTime, InputComponent* inputComponent)
{
	mInputManager.manageInput(mPlayer->mInputComponent);
	//mMovementManager.moveByInput(&mPlayer->mGeneralDataComponent->position, mPlayer->mMovementComponent, mPlayer->mInputComponent, deltaTime);
	// Update the camera
	/*playerView.setCenter(mPlayer->mGeneralDataComponent->position);
	rWindow->setView(playerView);*/

	// Draw calls
	for (auto tile : mTiles)
	{
		rWindow->draw(*tile);
	}
	
	rWindow->draw(*mPlayer->mCircleShapeComponent->mShape);

	rWindow->display();
}
