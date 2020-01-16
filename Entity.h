#pragma once

struct AnimationComponent;
struct CircleShapeComponent;
struct CollisionComponent;
struct CombatComponent;
struct GeneralDataComponent;
struct InputComponent;
struct InventoryComponent;
struct MovementComponent;
struct RectangleShapeComponent;
struct SpriteComponent;

enum COMPONENT
{
	ANIMATION_COMPONENT,
	CIRCLESHAPE_COMPONENT,
	COLLISION_COMPONENT,
	COMBAT_COMPONENT,
	GENERALDATA_COMPONENT,
	INPUT_COMPONENT,
	INVENTORY_COMPONENT,
	MOVEMENT_COMPONENT,
	RECTANGLESHAPE_COMPONENT,
	SPRITE_COMPONENT
};

class Entity
{
public:
	Entity();
	~Entity();

	AnimationComponent* mAnimationComponent{ nullptr };
	CircleShapeComponent* mCircleShapeComponent{ nullptr };
	CollisionComponent* mCollisionComponent{ nullptr };
	CombatComponent* mCombatComponent{ nullptr };
	GeneralDataComponent* mGeneralDataComponent{ nullptr };
	InputComponent* mInputComponent{ nullptr };
	InventoryComponent* mInventoryComponent{ nullptr };
	MovementComponent* mMovementComponent{ nullptr };
	RectangleShapeComponent* mRectangleShapeComponent{ nullptr };
	SpriteComponent* mSpriteComponent{ nullptr };

	void addComponent(int compEnum);
	void removeComponent(int compEnum);
	void removeAllComponents();
};

