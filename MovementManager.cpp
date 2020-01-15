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
	Vector2d movementVector;
	if (inputComp->keyW)
		movementVector.y -= 1;
	if (inputComp->keyA)
		movementVector.x -= 1;
	if (inputComp->keyS)
		movementVector.y += 1;
	if (inputComp->keyD)
		movementVector.x += 1;
	
	movementVector.normalize();
	
	float moveSpeed;
	if (inputComp->keyLShift)
		moveSpeed = moveComp->runSpeed;
	else
		moveSpeed = moveComp->walkSpeed;
	
	if (movementVector.x != 0)
		entityPos->x += movementVector.x * moveSpeed * deltaTime;
	if (movementVector.y != 0)
		entityPos->y += movementVector.y * moveSpeed * deltaTime;
}
