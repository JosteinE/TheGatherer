#include "MovementManager.h"
#include "MovementComponent.h"
#include "InputComponent.h"

MovementManager::MovementManager()
{
}

MovementManager::~MovementManager()
{
}

void MovementManager::moveByInput(sf::Vector2f* entityPos, MovementComponent * moveComp, InputComponent * inputComp, float deltaTime)
{
	sf::Vector2f movementVector;
	if (inputComp->keyW)
		movementVector.y -= 1;
	if (inputComp->keyA)
		movementVector.x -= 1;
	if (inputComp->keyS)
		movementVector.y += 1;
	if (inputComp->keyD)
		movementVector.x += 1;

	sf::Vector2f pos = *entityPos;

	if (inputComp->keyLShift)
		pos = (movementVector - pos) * moveComp->runSpeed * deltaTime;
	else
		pos = (movementVector - pos) * moveComp->walkSpeed * deltaTime;

	entityPos->x = pos.x;
	entityPos->y = pos.y;
}
