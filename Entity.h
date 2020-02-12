#pragma once

#include <vector>

struct AnimationComponent;
struct CircleShapeComponent;
struct CollisionComponent;
struct CombatComponent;
struct GeneralDataComponent;
struct HUDComponent;
struct InputComponent;
struct InventoryComponent;
struct ItemComponent;
struct MovementComponent;
struct NPCStateComponent;
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
	HUD_COMPONENT,
	INPUT_COMPONENT,
	INVENTORY_COMPONENT,
	ITEM_COMPONENT,
	MOVEMENT_COMPONENT,
	NPC_STATE_COMPONENT,
	RECTANGLESHAPE_COMPONENT,
	SPRITE_COMPONENT,
	TOOL_COMPONENT
};

class Entity
{
private:
	std::vector<Entity*> mChildren;

public:
	Entity(unsigned int inType, bool addGeneralComponent = true);
	~Entity();

	AnimationComponent* mAnimationComponent{ nullptr };
	CircleShapeComponent* mCircleShapeComponent{ nullptr };
	CollisionComponent* mCollisionComponent{ nullptr };
	CombatComponent* mCombatComponent{ nullptr };
	GeneralDataComponent* mGeneralDataComponent{ nullptr };
	std::vector<HUDComponent*>* mHUDComponent{ nullptr };
	InputComponent* mInputComponent{ nullptr };
	InventoryComponent* mInventoryComponent{ nullptr };
	ItemComponent * mItemComponent{ nullptr };
	MovementComponent* mMovementComponent{ nullptr };
	NPCStateComponent* mNPCStateComponent{ nullptr };
	RectangleShapeComponent* mRectangleShapeComponent{ nullptr };
	SpriteComponent* mSpriteComponent{ nullptr };
	ToolComponent * mToolComponent{ nullptr };


	void addComponent(int compEnum);
	void removeComponent(int compEnum);
	void removeAllComponents();

	void addChild(Entity* inChildEntity);
	void removeChild(Entity* inChildEntity);
	void removeChildren();
	std::vector<Entity*>* getChildren();
};

