#include "MovementManager.h"
#include "MovementComponent.h"
#include "InputComponent.h"

MovementManager::MovementManager()
{
}

MovementManager::~MovementManager()
{
}

void MovementManager::moveByInput(Vector2d* entityPos, MovementComponent * moveComp, InputComponent * inputComp, float deltaTime)
{
	Vector2d movementVector(0.f, 0.f);
	if (inputComp->keyW)
		movementVector.y -= 1;
	if (inputComp->keyA)
		movementVector.x -= 1;
	if (inputComp->keyS)
		movementVector.y += 1;
	if (inputComp->keyD)
		movementVector.x += 1;

	movementVector.normalize();

	if (inputComp->keyLShift)
		*entityPos = (movementVector - (*entityPos)) * moveComp->runSpeed * deltaTime;
	else
		*entityPos = (movementVector - (*entityPos)) * moveComp->walkSpeed * deltaTime;
}
