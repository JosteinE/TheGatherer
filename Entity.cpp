#include "Entity.h"
#include "AnimationComponent.h"
#include "CircleShapeComponent.h"
#include "CollisionComponent.h"
#include "CombatComponent.h"
#include "GeneralDataComponent.h"
#include "InputComponent.h"
#include "InventoryComponent.h"
#include "MovementComponent.h"
#include "RectangleShapeComponent.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	if (mAnimationComponent != nullptr)
		delete mAnimationComponent;
	if (mCircleShapeComponent != nullptr)
	{
		delete mCircleShapeComponent->mShape;
		delete mCircleShapeComponent;
	}
	if (mCombatComponent != nullptr)
		delete mCombatComponent;
	if (mGeneralDataComponent != nullptr)
		delete mGeneralDataComponent;
	if (mInputComponent != nullptr)
		delete mInputComponent;
	if (mInventoryComponent != nullptr)
		delete mInventoryComponent;
	if (mMovementComponent != nullptr)
		delete mMovementComponent;
	if (mRectangleShapeComponent != nullptr)
	{
		delete mRectangleShapeComponent->mShape;
		delete mRectangleShapeComponent;
	}
}

void Entity::addComponent(int compEnum)
{
	if (compEnum == ANIMATION_COMPONENT && mAnimationComponent == nullptr)
		mAnimationComponent = new AnimationComponent;

	if (compEnum == CIRCLESHAPE_COMPONENT && mCircleShapeComponent == nullptr)
		mCircleShapeComponent = new CircleShapeComponent;

	if (compEnum == COLLISION_COMPONENT && mCollisionComponent == nullptr)
		mCollisionComponent = new CollisionComponent;

	if (compEnum == COMBAT_COMPONENT && mCombatComponent == nullptr)
		mCombatComponent = new CombatComponent;

	if (compEnum == GENERALDATA_COMPONENT && mGeneralDataComponent == nullptr)
		mGeneralDataComponent = new GeneralDataComponent;

	if (compEnum == INPUT_COMPONENT && mInputComponent == nullptr)
		mInputComponent = new InputComponent;

	if (compEnum == INVENTORY_COMPONENT && mInventoryComponent == nullptr)
		mInventoryComponent = new InventoryComponent;

	if (compEnum == MOVEMENT_COMPONENT && mMovementComponent == nullptr)
		mMovementComponent = new MovementComponent;

	if (compEnum == RECTANGLESHAPE_COMPONENT && mRectangleShapeComponent == nullptr)
		mRectangleShapeComponent = new RectangleShapeComponent;
}

void Entity::removeComponent(int compEnum)
{
	if (compEnum == ANIMATION_COMPONENT && mAnimationComponent != nullptr)
	{
		delete mAnimationComponent;
		mAnimationComponent = nullptr;
	}

	if (compEnum == CIRCLESHAPE_COMPONENT && mCircleShapeComponent != nullptr)
	{
		delete mCircleShapeComponent->mShape;
		delete mCircleShapeComponent;
		mCircleShapeComponent = nullptr;
	}

	if (compEnum == COLLISION_COMPONENT && mCollisionComponent != nullptr)
	{
		delete mCollisionComponent;
		mCollisionComponent = nullptr;
	}

	if (compEnum == COMBAT_COMPONENT && mCombatComponent != nullptr)
	{
		delete mCombatComponent;
		mCombatComponent = nullptr;
	}

	if (compEnum == GENERALDATA_COMPONENT && mGeneralDataComponent != nullptr)
	{
		delete mGeneralDataComponent;
		mGeneralDataComponent = nullptr;
	}

	if (compEnum == INPUT_COMPONENT && mInputComponent != nullptr)
	{
		delete mInputComponent;
		mInputComponent = nullptr;
	}

	if (compEnum == INVENTORY_COMPONENT && mInventoryComponent != nullptr)
	{
		delete mInventoryComponent;
		mInventoryComponent = nullptr;
	}

	if (compEnum == MOVEMENT_COMPONENT && mMovementComponent != nullptr)
	{
		delete mMovementComponent;
		mMovementComponent = nullptr;
	}

	if (compEnum == RECTANGLESHAPE_COMPONENT && mRectangleShapeComponent != nullptr)
	{
		delete mRectangleShapeComponent->mShape;
		delete mRectangleShapeComponent;
		mRectangleShapeComponent = nullptr;
	}
}
