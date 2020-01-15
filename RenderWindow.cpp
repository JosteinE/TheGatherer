#include "RenderWindow.h"
#include "Entity.h"
#include "ComponentsHeader.h"
#include "LandscapeGenerator.h"

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
	mWorld.windowCenter = Vector2d(mWindow->getSize().x * 0.5f, mWindow->getSize().y * 0.5f);
	mWorld.playerView.setSize(sf::Vector2f(mWindow->getSize().x * (mWorld.viewSize * 0.01f), mWindow->getSize().y * (mWorld.viewSize * 0.01f)));
	mWorld.playerView.setCenter(mWorld.windowCenter.toSf());
	mWindow->setView(mWorld.playerView);

	// Entities
	std::vector<int> comps{ ANIMATION_COMPONENT, COLLISION_COMPONENT, COMBAT_COMPONENT,
							GENERALDATA_COMPONENT, INPUT_COMPONENT, INVENTORY_COMPONENT,
							MOVEMENT_COMPONENT, CIRCLESHAPE_COMPONENT };
	mEntityManager.addNewEntity(1, &comps);
	mPlayer = mEntityManager.getEntity(0);

	mPlayer->mGeneralDataComponent->name = "Player";
	mPlayer->mGeneralDataComponent->position = mWorld.windowCenter;
	mPlayer->mCircleShapeComponent->mShape = new sf::CircleShape(50.f);
	mPlayer->mCircleShapeComponent->mShape->setFillColor(sf::Color::Blue);
	mPlayer->mCircleShapeComponent->mShape->setPosition(mWorld.windowCenter.toSf());

	comps.clear();
	comps.insert(comps.end(), { GENERALDATA_COMPONENT, RECTANGLESHAPE_COMPONENT });

	for (int x = (mWorld.tileSetSize.x * -0.5f); x < (mWorld.tileSetSize.x * 0.5f); x++)
	{
		for (int y = (mWorld.tileSetSize.y * -0.5f); y < (mWorld.tileSetSize.y * 0.5f); y++)
		{
			mEntityManager.addNewEntity(0, &comps);
			mEntityManager.getLastEntity()->mRectangleShapeComponent->mShape = new sf::RectangleShape(mWorld.tileSize.toSf());
			mEntityManager.getLastEntity()->mRectangleShapeComponent->mShape->setFillColor(sf::Color::Green);
			mEntityManager.getLastEntity()->mRectangleShapeComponent->mShape->setPosition(sf::Vector2f(
				mWorld.windowCenter.x + (mWorld.tileSize.x * x * mWorld.tileSpacing.x),
				mWorld.windowCenter.y + (mWorld.tileSize.y * y * mWorld.tileSpacing.y)));
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
	mWorld.playerView.setCenter(mPlayer->mGeneralDataComponent->position.toSf());
	mWindow->setView(mWorld.playerView);

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
