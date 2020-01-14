#pragma once

struct AnimationComponent;
struct CombatComponent;
struct GeneralDataComponent;
struct InputComponent;
struct InventoryComponent;
struct MovementComponent;

class Entity
{
public:
	Entity();
	~Entity();

	AnimationComponent* mAnimationComponent{ nullptr };
	CombatComponent* mCombatComponent{ nullptr };
	GeneralDataComponent* mGeneralDataComponent{ nullptr };
	InputComponent* mInputComponent{ nullptr };
	InventoryComponent* mInventoryComponent{ nullptr };
	MovementComponent* mMovementComponent{ nullptr };
};

