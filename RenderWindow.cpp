#include "RenderWindow.h"
#include "Entity.h"
#include "EntityComponentsHeader.h"
#include "LandscapeGenerator.h"
#include "TileMap.h"
#include <SFML/Graphics/VertexArray.hpp>
#include "Items.h" // item ids

// World details
#include "WorldComponent.h"

RenderWindow::RenderWindow()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(1440, 900), "The Gatherer");
	mWindow->setFramerateLimit(FPS);
	mWindow->setVerticalSyncEnabled(bVerticalSyncEnabled);
}

RenderWindow::~RenderWindow()
{
	delete mWindow;
}

void RenderWindow::init()
{
	WorldComponent mWorld;

	// Build the player view
	playerView.setSize(sf::Vector2f(mWindow->getSize().x * (mWorld.camZoom * 0.01f), mWindow->getSize().y * (mWorld.camZoom * 0.01f)));
	playerView.setCenter(sf::Vector2f{0.f,0.f});
	mWindow->setView(playerView);

	// Entities
	std::vector<int> comps{ ANIMATION_COMPONENT, COLLISION_COMPONENT, COMBAT_COMPONENT,
							INPUT_COMPONENT, INVENTORY_COMPONENT, MOVEMENT_COMPONENT, SPRITE_COMPONENT };
	mEntityManager.createNewEntity(1, &comps);
	mPlayer = mEntityManager.getEntity(0);
	mPlayer->mGeneralDataComponent->name = "Player";
	mPlayer->mGeneralDataComponent->position = windowCenter;
	mSpriteManager.createSprite(mPlayer->mSpriteComponent, &mWorld.playerTexturePath);
	mPlayer->mSpriteComponent->mSprite->setScale(mWorld.playerSize.toSf());
	mAnimationManager.buildAnim(mPlayer->mAnimationComponent, mPlayer->mSpriteComponent, mWorld.playerSpriteSize);
	mSpriteManager.centerSpriteOrigin(mPlayer->mSpriteComponent, mPlayer->mAnimationComponent);
	mPlayer->mSpriteComponent->mSprite->setPosition(sf::Vector2f(0.f, 0.f));

	//Items
	mItemManager.setItemSet(mWorld.ItemSet, mWorld.ItemSize);
	mEntityManager.createNewItemEntity(&mItemManager, SWORD_ID, true, 1);
	mSpriteManager.setPosition(mEntityManager.getLastEntity()->mSpriteComponent, &mPlayer->mGeneralDataComponent->position);
	//*

	// Tiles
	LandscapeGenerator landGenerator;
	// Generate the tiles
	mLandscape = landGenerator.constructTileMap(mWorld.tileSet, mWorld.numTileTypes, Vector2d(0,0), &mWorld.tileSize, &mWorld.tileSetSize, false);
	// Shade the tiles
	landGenerator.shadeTileMap(mLandscape, 10, 5, 5, 50, 3);
	// Add Stones
	landGenerator.textureTileMap(mLandscape, 1, 10, 1, 1);
	// Add trees
	landGenerator.textureTileMap(mLandscape, 2, 10, 3, 3, true);
	// Clear the player spawn area (and paint it red)
	landGenerator.textureTileMap(mLandscape, 0, 0, 2, 2, false, &mPlayer->mGeneralDataComponent->position);
	landGenerator.colourTileMap(mLandscape, 255, 0, 0, 255, 0, 2, 2, false, &mPlayer->mGeneralDataComponent->position);
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
	mSpriteManager.setPosition(mPlayer->mSpriteComponent, &mPlayer->mGeneralDataComponent->position);
	mAnimationManager.updateAnimByInput(mPlayer->mSpriteComponent, mPlayer->mAnimationComponent, mPlayer->mInputComponent, 0);

	// Update the camera
	playerView.setCenter(mPlayer->mGeneralDataComponent->position.toSf());
	mWindow->setView(playerView);

	//Test (texture area surrounding the player)
	if (mPlayer->mInputComponent->keySpace)
	{
		for (auto tileIndex : mLandscape->getArea(mLandscape->getTileIndex(&mPlayer->mGeneralDataComponent->position), 1, 1, true))
		{
			mLandscape->setTileTexture(tileIndex, 0);
		}
	}

	// Draw calls
	mWindow->clear();

	for(auto layerIndex : mLandscape->getFrustum(mLandscape->getTileIndex(&mPlayer->mGeneralDataComponent->position), frustumTilesX, frustumTilesY))
		mWindow->draw(&(*mLandscape->getVertices())[layerIndex * 4], frustumTilesX * 2 * 4, sf::Quads, mLandscape->getTexture());

	for (unsigned int i = 0; i < 3; i++)
	{
		for (auto entity : *mEntityManager.getEntitiesFromLayer(i))
		{
			if (entity->mCircleShapeComponent != nullptr)
				mWindow->draw(*entity->mCircleShapeComponent->mShape);
			if (entity->mRectangleShapeComponent != nullptr)
				mWindow->draw(*entity->mRectangleShapeComponent->mShape);
			if (entity->mSpriteComponent != nullptr)
				mWindow->draw(*entity->mSpriteComponent->mSprite);
		}
	}
}
