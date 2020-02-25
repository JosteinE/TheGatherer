#include "RenderWindow.h"
#include "Entity.h"
#include "EntityComponentsHeader.h"
#include "LandscapeGenerator.h"
#include "TileMap.h"
#include <SFML/Graphics/VertexArray.hpp>
#include "Items.h" // item ids

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

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
	delete mEntitySpawner;
	delete mStateMachine;
	delete mWindow;
}

void RenderWindow::init()
{
	WorldComponent mWorld;
	
	mEntitySpawner = new EntitySpawner(&mEntityManager, &mSpriteManager, &mAnimationManager, &mWorld.spriteSize);

	camZoom = mWorld.camZoom;

	// Build the player view
	playerView.setSize(sf::Vector2f(mWindow->getSize().x * camZoom, mWindow->getSize().y * camZoom));
	playerView.setCenter(sf::Vector2f{0.f,0.f});
	mWindow->setView(playerView);

	// Load the items texture
	std::shared_ptr<sf::Texture> itemSet = std::make_shared<sf::Texture>();
	if (!itemSet->loadFromFile(mWorld.itemSet))
		std::cout << "Failed to load the item set" << std::endl;

	mItemManager.setItemSetAndSize(itemSet, mWorld.spriteSize.toSfu());

	// Tiles
	LandscapeGenerator landGenerator;
	// Generate the tiles
	mLandscape = landGenerator.constructTileMap(mWorld.tileSet, mWorld.numTileTypes, Vector2d(0, 0), &mWorld.spriteSize, &mWorld.tileSetSize, mWorld.centerMap, false);

	// Build the Player character
	std::vector<int> comps{ ANIMATION_COMPONENT, COLLISION_COMPONENT, COMBAT_COMPONENT, HUD_COMPONENT, HUD_COMPONENT,
							INPUT_COMPONENT, INVENTORY_COMPONENT, MOVEMENT_COMPONENT, SPRITE_COMPONENT };
	mEntityManager.createNewEntity(PLAYER_ENTITY, 1, &comps);
	mPlayer = mEntityManager.getLastEntity();
	mPlayer->mGeneralDataComponent->name = "Player";
	mPlayer->mGeneralDataComponent->position = mLandscape->mapCenter;
	// Player sprite
	mSpriteManager.createSprite(mPlayer->mSpriteComponent, &mWorld.playerTexturePath);
	mPlayer->mSpriteComponent->mSprite->setScale(mWorld.playerSize.toSf());
	mAnimationManager.buildAnim(mPlayer->mAnimationComponent, mPlayer->mSpriteComponent, mWorld.spriteSize);
	mSpriteManager.centerSpriteOrigin(mPlayer->mSpriteComponent, mPlayer->mAnimationComponent);
	//mPlayer->mSpriteComponent->mSprite->setPosition(mLandscape->mapCenter.toSf());
	// Player inventory
	mInventoryManager.init(mPlayer->mInventoryComponent);
	// Player HUD
	(*mPlayer->mHUDComponent)[0]->initialText = "Wood: ";
	(*mPlayer->mHUDComponent)[0]->textRelativePos = sf::Vector2i{-50, -40};
	(*mPlayer->mHUDComponent)[1]->initialText = "Minerals: ";
	(*mPlayer->mHUDComponent)[1]->textRelativePos = sf::Vector2i{ 10, -40 };
	mHUDManager.buildHUDComponent((*mPlayer->mHUDComponent)[0]);
	mHUDManager.buildHUDComponent((*mPlayer->mHUDComponent)[1]);
	mHUDManager.updateHUDText((*mPlayer->mHUDComponent)[0], (*mPlayer->mHUDComponent)[0]->initialText + std::to_string(mPlayer->mInventoryComponent->numWood));
	mHUDManager.updateHUDText((*mPlayer->mHUDComponent)[1], (*mPlayer->mHUDComponent)[1]->initialText + std::to_string(mPlayer->mInventoryComponent->numMinerals));

	// Menus
	mCraftingMenu.constructMenu(CRAFTING_MENU, &mWorld.fontPath, &mWorld.itemSet);

	//Items
	mEntityManager.createNewItemEntity(&mItemManager, SWORD_ID, true, 1);
	mSpriteManager.setPosition(mEntityManager.getLastEntity()->mSpriteComponent, Vector2d(0, 2));

	mEntityManager.createNewItemEntity(&mItemManager, AXE_ID, true, 1);
	mSpriteManager.setPosition(mEntityManager.getLastEntity()->mSpriteComponent, Vector2d(1, -2));


	// Landscape
	// Add Stones
	landGenerator.textureTileMap(mLandscape, 1, 10, 1, 1, true);
	// Add trees
	landGenerator.textureTileMap(mLandscape, 2, 3, 3, 3, true);
	// Colour random areas
	landGenerator.colourTileMap(mLandscape, 255, 200, 255, 255, 1, 0, 0, 5, 5, true);	// Purple
	landGenerator.colourTileMap(mLandscape, 200, 200, 255, 255, 1, 0, 0, 5, 5, true);	// Blue
	landGenerator.colourTileMap(mLandscape, 255, 200, 200, 255, 1, 0, 0, 5, 5, true);	// Red
	// Shade the tiles	
	landGenerator.shadeTileMap(mLandscape, 10, 5, 5, 50, 3);
	//Clear the player spawn area (and colour shade it)
	landGenerator.textureTileMap(mLandscape, 0, 0, 2, 2, false, &mPlayer->mGeneralDataComponent->position);
	landGenerator.colourShadeTileMap(mLandscape, 200, 0, 255, 255, 0.1, 5, 5, 10, 10, 10, true);

	//TESTING SPAWNER & AI 
	comps.clear();
	comps.insert(comps.end(), { ANIMATION_COMPONENT, COLLISION_COMPONENT, COMBAT_COMPONENT, MOVEMENT_COMPONENT, NPC_STATE_COMPONENT, SPRITE_COMPONENT });
	mEntitySpawner->SpawnEntities(NPC_ENTITY, &comps, 1, mPlayer->mGeneralDataComponent->position - Vector2d(100.f, 100.f),
											 mPlayer->mGeneralDataComponent->position + Vector2d(100.f, 100.f),
								  50, 100, &mWorld.playerTexturePath);
	mStateMachine = new StateMachine(&mMovementManager, &mPlayer->mGeneralDataComponent->position);
}

void RenderWindow::tick(float deltaTime)
{
	std::cout << "playerPos: " << mPlayer->mGeneralDataComponent->position << std::endl;
	// Close if escape is pressed
	if (mPlayer->mInputComponent->keyESC)
		mWindow->close();

	// Move and update the player character
	mMovementManager.moveByInput(&mPlayer->mGeneralDataComponent->position, mPlayer->mMovementComponent, mPlayer->mInputComponent, deltaTime);
	mSpriteManager.setPosition(mPlayer->mSpriteComponent, mPlayer->mGeneralDataComponent->position);
	mAnimationManager.updateAnimByInput(mPlayer->mSpriteComponent, mPlayer->mAnimationComponent, mPlayer->mInputComponent, 0);

	// Check for player collision
	if (mCollisionManager.isColliding(&mPlayer->mGeneralDataComponent->position, mPlayer->mCollisionComponent, mLandscape.get()))
		mPlayer->mGeneralDataComponent->position = mPlayerLastPos;
	else
		mPlayerLastPos = mPlayer->mGeneralDataComponent->position;

	// Update the camera
	playerView.setCenter(mPlayer->mGeneralDataComponent->position.toSf());
	mWindow->setView(playerView);

	// Update the HUD position
	mHUDManager.updateHUDPosition(mPlayer->mHUDComponent, &mPlayer->mGeneralDataComponent->position);

	//TEST AREA START
	//Harvest surrounding area
	if (mPlayer->mInputComponent->keySpace)
	{
		for (auto tileIndex : mLandscape->getArea(mLandscape->getTileIndex(&mPlayer->mGeneralDataComponent->position), 1, 1, true))
		{
			mLandscape->setTileTexture(tileIndex, 0);
		}
	}

	//Harvest entity clicked on
	if (mPlayer->mInputComponent->LMB)
	{
		mInventoryManager.harvestTile(mInputManager.getRelativeMousePosition(mPlayer->mInputComponent, sf::Vector2i(mWindow->getSize().x * 0.5f, mWindow->getSize().y * 0.5f), camZoom),
									  mLandscape.get(), mPlayer->mGeneralDataComponent, mPlayer->mInventoryComponent);

		mHUDManager.updateHUDText((*mPlayer->mHUDComponent)[0], (*mPlayer->mHUDComponent)[0]->initialText + std::to_string(mPlayer->mInventoryComponent->numWood));
		mHUDManager.updateHUDText((*mPlayer->mHUDComponent)[1], (*mPlayer->mHUDComponent)[1]->initialText + std::to_string(mPlayer->mInventoryComponent->numMinerals));
	}

	//Harvest entity clicked on
	mCraftingMenu.toggleVis(mPlayer->mInputComponent->keyE);


	for (Entity* entity : *mEntityManager.getEntities(NPC_ENTITY))
	{
		if (entity->mNPCStateComponent != nullptr)
		{
			mStateMachine->runMachine(deltaTime, &entity->mGeneralDataComponent->position,
									  entity->mMovementComponent, entity->mNPCStateComponent,
									  entity->mCombatComponent);
			mSpriteManager.setPosition(entity->mSpriteComponent, entity->mGeneralDataComponent->position);
		}
	}

	// TEST AREA END


	// Draw calls
	mWindow->clear();

	//mWindow->draw(*mLandscape->getVertices());

	for(auto layerIndex : mLandscape->getFrustum(mLandscape->getTileIndex(&mPlayer->mGeneralDataComponent->position), frustumTilesX + (camZoom * 0), frustumTilesY + (camZoom * 0))) // 48, 32
		mWindow->draw(&(*mLandscape->getVertices())[layerIndex * 4], (frustumTilesX + (camZoom * 0)) * 2 * 4, sf::Quads, mLandscape->getTexture()); // 48


	// Section TEST
	for (Entity* entity : *mEntityManager.getRenderSection(&mPlayer->mGeneralDataComponent->position))
	{
		if (entity->mCircleShapeComponent != nullptr)
			mWindow->draw(*entity->mCircleShapeComponent->mShape);
		if (entity->mRectangleShapeComponent != nullptr)
			mWindow->draw(*entity->mRectangleShapeComponent->mShape);
		if (entity->mSpriteComponent != nullptr)
			mWindow->draw(*entity->mSpriteComponent->mSprite);
		if (entity->mHUDComponent != nullptr)
			for (auto hudComp : *entity->mHUDComponent)
				mWindow->draw(hudComp->mText);
	}


	//for (unsigned int i = 0; i < 3; i++)
	//{
	//	for (auto entity : *mEntityManager.getEntitiesFromLayer(i))
	//	{
	//		if (entity->mCircleShapeComponent != nullptr)
	//			mWindow->draw(*entity->mCircleShapeComponent->mShape);
	//		if (entity->mRectangleShapeComponent != nullptr)
	//			mWindow->draw(*entity->mRectangleShapeComponent->mShape);
	//		if (entity->mSpriteComponent != nullptr)
	//			mWindow->draw(*entity->mSpriteComponent->mSprite);
	//		if (entity->mHUDComponent != nullptr)
	//			for (auto hudComp : *entity->mHUDComponent)
	//				mWindow->draw(hudComp->mText);
	//	}
	//}
	mCraftingMenu.draw(*mWindow, &mPlayer->mGeneralDataComponent->position);
}

void RenderWindow::zoomCamera(int zoomAmount)
{
	playerView.setSize(playerView.getSize().x / camZoom, playerView.getSize().y / camZoom);
	camZoom += zoomAmount * 0.01;
	playerView.setSize(playerView.getSize().x * camZoom, playerView.getSize().y * camZoom);
}
