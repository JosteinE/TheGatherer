#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
	if (mAnimationComponent != nullptr)
		delete mAnimationComponent;
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
}
