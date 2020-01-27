#pragma once

struct AnimationComponent;
struct CircleShapeComponent;
struct CollisionComponent;
struct CombatComponent;
struct GeneralDataComponent;
struct InputComponent;
struct InventoryComponent;
struct ItemComponent;
struct MovementComponent;
struct RectangleShapeComponent;
struct SpriteComponent;
struct ToolComponent;

enum COMPONENT
{
	ANIMATION_COMPONENT,
	CIRCLESHAPE_COMPONENT,
	COLLISION_COMPONENT,
	COMBAT_COMPONENT,
	GENERALDATA_COMPONENT,
	INPUT_COMPONENT,
	INVENTORY_COMPONENT,
	ITEM_COMPONENT,
	MOVEMENT_COMPONENT,
	RECTANGLESHAPE_COMPONENT,
	SPRITE_COMPONENT,
	TOOL_COMPONENT
};

class Entity
{
public:
	Entity(bool addGeneralComponent = true);
	~Entity();

	AnimationComponent* mAnimationComponent{ nullptr };
	CircleShapeComponent* mCircleShapeComponent{ nullptr };
	CollisionComponent* mCollisionComponent{ nullptr };
	CombatComponent* mCombatComponent{ nullptr };
	GeneralDataComponent* mGeneralDataComponent{ nullptr };
	InputComponent* mInputComponent{ nullptr };
	InventoryComponent* mInventoryComponent{ nullptr };
	ItemComponent * mItemComponent{ nullptr };
	MovementComponent* mMovementComponent{ nullptr };
	RectangleShapeComponent* mRectangleShapeComponent{ nullptr };
	SpriteComponent* mSpriteComponent{ nullptr };
	ToolComponent * mToolComponent{ nullptr };


	void addComponent(int compEnum);
	void removeComponent(int compEnum);
	void removeAllComponents();
};

