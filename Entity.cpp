#include "Entity.h"
#include "EntityComponentsHeader.h"
#include <algorithm> // std::find

Entity::Entity(unsigned int inType, bool addGeneralComponent)
{
	mType = inType;

	if(addGeneralComponent)
		addComponent(GENERALDATA_COMPONENT);
}

Entity::~Entity()
{
	removeChildren();
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

	else if (compEnum == HUD_COMPONENT)
	{
		if (mHUDComponent == nullptr)
			mHUDComponent = new std::vector<HUDComponent*>;
		mHUDComponent->push_back(new HUDComponent);
	}

	else if (compEnum == INPUT_COMPONENT && mInputComponent == nullptr)
		mInputComponent = new InputComponent;

	else if (compEnum == INVENTORY_COMPONENT && mInventoryComponent == nullptr)
		mInventoryComponent = new InventoryComponent;

	else if (compEnum == ITEM_COMPONENT && mItemComponent == nullptr)
		mItemComponent = new ItemComponent;

	else if (compEnum == MOVEMENT_COMPONENT && mMovementComponent == nullptr)
		mMovementComponent = new MovementComponent;

	else if (compEnum == NPC_STATE_COMPONENT && mNPCStateComponent == nullptr)
		mNPCStateComponent = new NPCStateComponent;

	else if (compEnum == RECTANGLESHAPE_COMPONENT && mRectangleShapeComponent == nullptr)
		mRectangleShapeComponent = new RectangleShapeComponent;

	else if (compEnum == SPRITE_COMPONENT && mSpriteComponent == nullptr)
		mSpriteComponent = new SpriteComponent;

	else if (compEnum == TOOL_COMPONENT && mToolComponent == nullptr)
		mToolComponent = new ToolComponent;

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

	else if (compEnum == HUD_COMPONENT && mHUDComponent != nullptr)
	{
		for (auto HUDComp : *mHUDComponent)
		{
			delete HUDComp;
		}
		mHUDComponent->clear();
		delete mHUDComponent;
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

	else if (compEnum == ITEM_COMPONENT && mItemComponent != nullptr)
	{
		delete mItemComponent;
		mItemComponent = nullptr;
	}

	else if (compEnum == MOVEMENT_COMPONENT && mMovementComponent != nullptr)
	{
		delete mMovementComponent;
		mMovementComponent = nullptr;
	}

	else if (compEnum == NPC_STATE_COMPONENT && mNPCStateComponent != nullptr)
	{
		delete mNPCStateComponent;
		mNPCStateComponent = nullptr;
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

	else if (compEnum == TOOL_COMPONENT && mToolComponent != nullptr)
	{
		delete mToolComponent;
		mToolComponent = nullptr;
	}
}

void Entity::removeAllComponents()
{
	removeComponent(ANIMATION_COMPONENT);
	removeComponent(CIRCLESHAPE_COMPONENT);
	removeComponent(COLLISION_COMPONENT);
	removeComponent(COMBAT_COMPONENT);
	removeComponent(GENERALDATA_COMPONENT);
	removeComponent(HUD_COMPONENT);
	removeComponent(INPUT_COMPONENT);
	removeComponent(INVENTORY_COMPONENT);
	removeComponent(MOVEMENT_COMPONENT);
	removeComponent(NPC_STATE_COMPONENT);
	removeComponent(RECTANGLESHAPE_COMPONENT);
	removeComponent(SPRITE_COMPONENT);
}

void Entity::addChild(Entity * inChildEntity)
{
	mChildren.push_back(inChildEntity);
	inChildEntity->mGeneralDataComponent->isChild = true;
	inChildEntity->mGeneralDataComponent->origin = &inChildEntity->mGeneralDataComponent->position;
}

void Entity::removeChild(Entity * inChildEntity)
{
	std::vector<Entity*>::iterator it = std::find(mChildren.begin(), mChildren.end(), inChildEntity);
	if (it != mChildren.end())
		mChildren.erase(it);
}

void Entity::removeChildren()
{
	mChildren.clear();
}

std::vector<Entity*>* Entity::getChildren()
{
	return &mChildren;
}
