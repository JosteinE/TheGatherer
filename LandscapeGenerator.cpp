#include "LandscapeGenerator.h"
#include "EntityManager.h"
#include "RectangleShapeComponent.h"

LandscapeGenerator::LandscapeGenerator(const std::string& tileset, Vector2d inPosition, Vector2d * inTileSize, Vector2d * inTileSetSize, Vector2d * inTileSpacing)
{
	setPosition(inPosition);
	setTileSize(inTileSize);
	setTileSetSize(inTileSetSize);
	setTileSpacing(inTileSpacing);
}

LandscapeGenerator::~LandscapeGenerator()
{
}

void LandscapeGenerator::setPosition(Vector2d inPosition)
{
		mPosition = inPosition;
}

void LandscapeGenerator::setTileSize(Vector2d * inTileSize)
{
	if (inTileSize != nullptr)
		mTileSize = inTileSize;
}

void LandscapeGenerator::setTileSetSize(Vector2d * inTileSetSize)
{
	if (inTileSetSize != nullptr)
		mTileSetSize = inTileSetSize;
}

void LandscapeGenerator::setTileSpacing(Vector2d * inTileSpacing)
{
	if (inTileSpacing != nullptr)
		mTileSpacing = inTileSpacing;
}

void LandscapeGenerator::setTexture(const std::string* filePath)
{
	if (filePath != nullptr && mTexturePath != *filePath)
	{
		mTexturePath = *filePath;
		mTexture = std::make_shared<sf::Texture>();
		
		if (mTexture->loadFromFile(mTexturePath))
			bTextureLoaded = true;
	}
}

void LandscapeGenerator::construct(EntityManager * entM, std::vector<int>* components)
{
	for (int x = (mTileSetSize->x * -0.5f); x < (mTileSetSize->x * 0.5f); x++)
	{
		for (int y = (mTileSetSize->y * -0.5f); y < (mTileSetSize->y * 0.5f); y++)
		{
			entM->addNewEntity(0, components);
			entM->getLastEntity()->mRectangleShapeComponent->mShape = new sf::RectangleShape(mTileSize->toSf());
			entM->getLastEntity()->mRectangleShapeComponent->mShape->setFillColor(sf::Color::Green);
			entM->getLastEntity()->mRectangleShapeComponent->mShape->setPosition(sf::Vector2f(
				mPosition.x + (mTileSize->x * x * mTileSpacing->x),
				mPosition.y + (mTileSize->y * y * mTileSpacing->y)));

			if (bTextureLoaded)
			{
				entM->getLastEntity()->mRectangleShapeComponent->mTexturePath = mTexturePath;
				entM->getLastEntity()->mRectangleShapeComponent->mTexture = mTexture;
				entM->getLastEntity()->mRectangleShapeComponent->mShape->setTexture(mTexture.get());
			}
		}
	}
}
