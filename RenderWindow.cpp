#include "RenderWindow.h"
#include "Entity.h"
#include "EntityComponentsHeader.h"
#include "LandscapeGenerator.h"
#include "TileMap.h"

// World details
#include "WorldComponent.h"

RenderWindow::RenderWindow()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(1440, 900), "The Gatherer");
}

RenderWindow::~RenderWindow()
{
	delete mWindow;
}

void RenderWindow::init()
{
	WorldComponent mWorld;

	// Build the player view
	//windowCenter = Vector2d(mWindow->getSize().x * 0.5f, mWindow->getSize().y * 0.5f);
	playerView.setSize(sf::Vector2f(mWindow->getSize().x * (mWorld.camZoom * 0.01f), mWindow->getSize().y * (mWorld.camZoom * 0.01f)));
	//playerView.setCenter(windowCenter.toSf());
	playerView.setCenter(sf::Vector2f{0.f,0.f});
	mWindow->setView(playerView);

	// Entities
	std::vector<int> comps{ ANIMATION_COMPONENT, COLLISION_COMPONENT, COMBAT_COMPONENT,
							INPUT_COMPONENT, INVENTORY_COMPONENT, MOVEMENT_COMPONENT, SPRITE_COMPONENT };
	mEntityManager.addNewEntity(1, &comps);
	mPlayer = mEntityManager.getEntity(0);
	mPlayer->mGeneralDataComponent->name = "Player";
	mPlayer->mGeneralDataComponent->position = windowCenter;
	mPlayer->mSpriteComponent->mTexture = std::make_shared<sf::Texture>();
	mPlayer->mSpriteComponent->mTexture->loadFromFile(mWorld.playerTexturePath);
	mPlayer->mSpriteComponent->mSprite = new sf::Sprite(*mPlayer->mSpriteComponent->mTexture);
	mPlayer->mSpriteComponent->mSprite->setOrigin(sf::Vector2f(mPlayer->mSpriteComponent->mTexture->getSize().x * 0.5f, mPlayer->mSpriteComponent->mTexture->getSize().x * 0.5f));
	mPlayer->mSpriteComponent->mSprite->setPosition(sf::Vector2f(0.f, 0.f));
	mPlayer->mSpriteComponent->mSprite->setScale(mWorld.playerSize.toSf());

	// Tiles
	comps.clear();
	comps.insert(comps.end(), { RECTANGLESHAPE_COMPONENT });
	LandscapeGenerator landGenerator(mWorld.tileSet, Vector2d{0.f, 0.f}, &mWorld.tileSize, &mWorld.tileSetSize, &mWorld.tileSpacing);
	landGenerator.setTexture(&mWorld.tileTexture);
	landGenerator.construct(&mEntityManager, &comps);

	mLandscape = new TileMap(mWorld.tileSet, mWorld.tileSize, )

	// VertexArray Test
	triangle = new sf::VertexArray(sf::Triangles, 3);

	// define the position of the triangle's points
	(*triangle)[0].position = sf::Vector2f(0.f, 0.f);
	(*triangle)[1].position = sf::Vector2f(50.f, 0.f);
	(*triangle)[2].position = sf::Vector2f(50.f, 50.f);

	// define the color of the triangle's points
	(*triangle)[0].color = sf::Color::Red;
	(*triangle)[1].color = sf::Color::Blue;
	(*triangle)[2].color = sf::Color::Green;
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
	mShapeManager.updateShapePosition(mPlayer->mSpriteComponent, &mPlayer->mGeneralDataComponent->position);

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
			if (entity->mSpriteComponent != nullptr)
				mWindow->draw(*entity->mSpriteComponent->mSprite);
		}
	}
	mWindow->draw(*triangle);
}
