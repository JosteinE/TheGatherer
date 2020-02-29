#include "EntityRenderer.h"

#include "Entity.h"
#include "CircleShapeComponent.h"
#include "RectangleShapeComponent.h"
#include "SpriteComponent.h"
#include "HUDComponent.h"
#include "GeneralDataComponent.h"

EntityRenderer::EntityRenderer()
{
}


EntityRenderer::~EntityRenderer()
{
}

void EntityRenderer::setLightPosition(sf::Shader * shader, Entity * inEntity)
{
	shader->setUniform("lightPos", inEntity->mGeneralDataComponent->position.toSf());
}

void EntityRenderer::drawEntity(sf::RenderTarget & target, sf::Shader * shader, Entity * inEntity)
{
	if (inEntity->mCircleShapeComponent != nullptr)
		target.draw(*inEntity->mCircleShapeComponent->mShape, shader);
	if (inEntity->mRectangleShapeComponent != nullptr)
		target.draw(*inEntity->mRectangleShapeComponent->mShape, shader);
	if (inEntity->mSpriteComponent != nullptr)
		target.draw(*inEntity->mSpriteComponent->mSprite, shader);
	if (inEntity->mHUDComponent != nullptr)
		for (HUDComponent* hudComp : *inEntity->mHUDComponent)
			target.draw(hudComp->mText);
}
