#include "Entity.h"
#include "EntityComponentsHeader.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	removeAllComponents();
}

void Entity::addComponent(int compEnum)
{
	if (compEnum == ANIMATION_COMPONENT && mAnimationComponent == nullptr)
		mAnimationComponent = new AnimationComponent;

	else if (compEnum == CIRCLESHAPE_COMPONENT && mCircleShapeComponent == nullptr)
		mCircleShapeComponent = new CircleShapeComponent;

	else if (compEnum == COLLISION_COMPONENT && mCollisionComponent == nullptr)
		mCollisionComponent = new CollisionComponent;

	else if (compEnum == COMBAT_COMPONENT && mCombatComponent == nullptr)
		mCombatComponent = new CombatComponent;

	else if (compEnum == GENERALDATA_COMPONENT && mGeneralDataComponent == nullptr)
		mGeneralDataComponent = new GeneralDataComponent;

	else if (compEnum == INPUT_COMPONENT && mInputComponent == nullptr)
		mInputComponent = new InputComponent;

	else if (compEnum == INVENTORY_COMPONENT && mInventoryComponent == nullptr)
		mInventoryComponent = new InventoryComponent;

	else if (compEnum == MOVEMENT_COMPONENT && mMovementComponent == nullptr)
		mMovementComponent = new MovementComponent;

	else if (compEnum == RECTANGLESHAPE_COMPONENT && mRectangleShapeComponent == nullptr)
		mRectangleShapeComponent = new RectangleShapeComponent;

	else if (compEnum == SPRITE_COMPONENT && mSpriteComponent == nullptr)
		mSpriteComponent = new SpriteComponent;

	else
		std::cout << "Could not add the component(" << compEnum << ") because it is already added or does not exist!" << std::endl;
}

void Entity::removeComponent(int compEnum)
{
	if (compEnum == ANIMATION_COMPONENT && mAnimationComponent != nullptr)
	{
		delete mAnimationComponent;
		mAnimationComponent = nullptr;
	}

	else if (compEnum == CIRCLESHAPE_COMPONENT && mCircleShapeComponent != nullptr)
	{
		delete mCircleShapeComponent->mShape;
		delete mCircleShapeComponent;
		mCircleShapeComponent = nullptr;
	}

	else if (compEnum == COLLISION_COMPONENT && mCollisionComponent != nullptr)
	{
		delete mCollisionComponent;
		mCollisionComponent = nullptr;
	}

	else if (compEnum == COMBAT_COMPONENT && mCombatComponent != nullptr)
	{
		delete mCombatComponent;
		mCombatComponent = nullptr;
	}

	else if (compEnum == GENERALDATA_COMPONENT && mGeneralDataComponent != nullptr)
	{
		delete mGeneralDataComponent;
		mGeneralDataComponent = nullptr;
	}

	else if (compEnum == INPUT_COMPONENT && mInputComponent != nullptr)
	{
		delete mInputComponent;
		mInputComponent = nullptr;
	}

	else if (compEnum == INVENTORY_COMPONENT && mInventoryComponent != nullptr)
	{
		delete mInventoryComponent;
		mInventoryComponent = nullptr;
	}

	else if (compEnum == MOVEMENT_COMPONENT && mMovementComponent != nullptr)
	{
		delete mMovementComponent;
		mMovementComponent = nullptr;
	}

	else if (compEnum == RECTANGLESHAPE_COMPONENT && mRectangleShapeComponent != nullptr)
	{
		delete mRectangleShapeComponent->mShape;
		delete mRectangleShapeComponent;
		mRectangleShapeComponent = nullptr;
	}

	else if (compEnum == SPRITE_COMPONENT && mSpriteComponent != nullptr)
	{
		delete mSpriteComponent->mSprite;
		delete mSpriteComponent;
		mSpriteComponent = nullptr;
	}
}

void Entity::removeAllComponents()
{
	removeComponent(ANIMATION_COMPONENT);
	removeComponent(CIRCLESHAPE_COMPONENT);
	removeComponent(COLLISION_COMPONENT);
	removeComponent(COMBAT_COMPONENT);
	removeComponent(GENERALDATA_COMPONENT);
	removeComponent(INPUT_COMPONENT);
	removeComponent(INVENTORY_COMPONENT);
	removeComponent(MOVEMENT_COMPONENT);
	removeComponent(RECTANGLESHAPE_COMPONENT);
	removeComponent(SPRITE_COMPONENT);
}