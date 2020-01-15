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

	// Tiles
	comps.clear();
	comps.insert(comps.end(), { GENERALDATA_COMPONENT, RECTANGLESHAPE_COMPONENT });
	LandscapeGenerator lGenerator(&mWorld.windowCenter, &mWorld.tileSize, &mWorld.tileSetSize, &mWorld.tileSpacing);
	lGenerator.construct(&mEntityManager, &comps);
}

void RenderWindow::tick(float deltaTime)
{
	// Register input
	mInputManager.registerInput(mPlayer->mInputComponent);

	// Close if escape is pressed
	if (mPlayer->mInputComponent->keyESC)
		mWindow->close();

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
