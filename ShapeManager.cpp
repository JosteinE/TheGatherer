#include "ShapeManager.h"
#include "CircleShapeComponent.h"
#include "RectangleShapeComponent.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


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
