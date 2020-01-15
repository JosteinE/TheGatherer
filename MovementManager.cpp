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

	if (movementVector.x != 0 && movementVector.y != 0)
	{
		if (inputComp->keyLShift)
		{
			entityPos->x *= movementVector.x * moveComp->runSpeed * deltaTime;
			entityPos->y *= movementVector.y * moveComp->runSpeed * deltaTime;
		}
		else
		{
			entityPos->x *= movementVector.x * moveComp->walkSpeed * deltaTime;
			entityPos->y *= movementVector.y * moveComp->walkSpeed * deltaTime;
		}
	}
}
