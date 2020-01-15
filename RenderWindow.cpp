#include "RenderWindow.h"
#include "Entity.h"
#include "ComponentsHeader.h"

RenderWindow::RenderWindow()
{
	//Window
	mWindow = new sf::RenderWindow(sf::VideoMode(1440, 900), "The Gatherer");
}

RenderWindow::~RenderWindow()
{
	mTiles.clear();

	delete mWindow;
}

void RenderWindow::init()
{
	// Build player pov
	mWindowCenter = Vector2d(mWindow->getSize().x * 0.5f, mWindow->getSize().y * 0.5f);
	playerView.setSize(sf::Vector2f(mWindow->getSize().x * (viewSize * 0.01f), mWindow->getSize().y * (viewSize * 0.01f)));
	playerView.setCenter(mWindowCenter.toSf());
	mWindow->setView(playerView);

	// Entities
	std::vector<int> comps{ ANIMATION_COMPONENT, COLLISION_COMPONENT, COMBAT_COMPONENT,
							GENERALDATA_COMPONENT, INPUT_COMPONENT, INVENTORY_COMPONENT,
							MOVEMENT_COMPONENT, CIRCLESHAPE_COMPONENT };
	mEntityManager.addNewEntity(1, &comps);
	mPlayer = mEntityManager.getEntity(0);

	mPlayer->mGeneralDataComponent->name = "Player";
	mPlayer->mGeneralDataComponent->position = mWindowCenter;
	mPlayer->mCircleShapeComponent->mShape = new sf::CircleShape(50.f);
	mPlayer->mCircleShapeComponent->mShape->setFillColor(sf::Color::Blue);
	mPlayer->mCircleShapeComponent->mShape->setPosition(mWindowCenter.toSf());

	comps.clear();
	comps.insert(comps.end(), { GENERALDATA_COMPONENT, RECTANGLESHAPE_COMPONENT });

	for (int x = (tileSetSize.x * -0.5f); x < (tileSetSize.x * 0.5f); x++)
	{
		for (int y = (tileSetSize.y * -0.5f); y < (tileSetSize.y * 0.5f); y++)
		{
			mEntityManager.addNewEntity(0, &comps);
			mEntityManager.getLastEntity()->mRectangleShapeComponent->mShape = new sf::RectangleShape(tileSize.toSf());
			mEntityManager.getLastEntity()->mRectangleShapeComponent->mShape->setFillColor(sf::Color::Green);
			mEntityManager.getLastEntity()->mRectangleShapeComponent->mShape->setPosition(sf::Vector2f(
				mWindowCenter.x + (tileSize.x * x * tileSpacing.x),
				mWindowCenter.y + (tileSize.y * y * tileSpacing.y)));
			mTiles.push_back(mEntityManager.getLastEntity());
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
	mWindow->clear();
	for (unsigned int i = 0; i < 3; i++)
	{
		for (auto entity : *mEntityManager.getEntitiesFromLayer(i))
		{
			if (entity->mCircleShapeComponent != nullptr)
				mWindow->draw(*entity->mCircleShapeComponent->mShape);
			if (entity->mRectangleShapeComponent != nullptr)
				mWindow->draw(*entity->mRectangleShapeComponent->mShape);
		}
	}
	mWindow->display();
}
