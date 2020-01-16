#include "ShapeManager.h"
#include "CircleShapeComponent.h"
#include "RectangleShapeComponent.h"
#include "SpriteComponent.h"
#include <SFML/Graphics.hpp>


ShapeManager::ShapeManager()
{
}

ShapeManager::~ShapeManager()
{
}

void ShapeManager::updateShapePosition(CircleShapeComponent * inShape, Vector2d * inPos)
{
	inShape->mShape->setPosition(inPos->toSf());
}

void ShapeManager::updateShapePosition(RectangleShapeComponent * inShape, Vector2d * inPos)
{
	inShape->mShape->setPosition(inPos->toSf());
}

void ShapeManager::updateShapePosition(SpriteComponent * inShape, Vector2d * inPos)
{
	inShape->mSprite->setPosition(inPos->toSf());
}
