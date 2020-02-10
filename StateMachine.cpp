#include "StateMachine.h"
#include "NPCStateComponent.h"
#include "GeneralDataComponent.h"
#include "CombatComponent.h"
#include "MovementComponent.h"
#include <ctime>


StateMachine::StateMachine(MovementManager* inMovementManager, Vector2d* inPlayerPos)
{
	// Activate the randomizer.
	srand(static_cast<unsigned int>(time(NULL)));

	movementManager = inMovementManager;
	playerPos = inPlayerPos;
}


StateMachine::~StateMachine()
{
}

void StateMachine::notify(NPCStateComponent * npcStateComp, int notification)
{
	npcStateComp->notificationQueue.push(notification);
	npcStateComp->state = LEARN;
}

Vector2d StateMachine::generateDestination(Vector2d * position, NPCStateComponent * npcStateComp, Vector2d * areaMin, Vector2d * areaMax)
{
	Vector2d newDestination;

	if(areaMin != nullptr && areaMax != nullptr)
		newDestination = Vector2d{ areaMin->x + (rand() % static_cast<int>(areaMax->x - areaMin->x)),
								   areaMin->y + (rand() % static_cast<int>(areaMax->y - areaMin->y)) };
	else
	{
		newDestination = Vector2d{ rand() % maxDestinationDistance,
								   rand() % maxDestinationDistance };
		if (rand() % 2 == 0) // 0 or 1
			newDestination.x *= -1;
		if (rand() % 2 == 0) // 0 or 1
			newDestination.y *= -1;

		newDestination.x += position->x;
		newDestination.y += position->y;
	}

	return newDestination;
}

bool StateMachine::isDestinationWithinRange(Vector2d * position, Vector2d * destination, int maxRange)
{
	Vector2d distance = (*destination) - (*position);
	if (distance.length() <= maxRange)
		return true;
	else
		return false;
}

void StateMachine::runMachine(float deltaTime, Vector2d* position, MovementComponent* moveComp, NPCStateComponent* npcStateComp, CombatComponent* combatComp)
{
	if (npcStateComp->state == LEARN) learn(position, npcStateComp);
	if (npcStateComp->state == PATROL) patrol(position, moveComp, npcStateComp, deltaTime);
	if (npcStateComp->state == CHASE) chase(position, moveComp, npcStateComp, deltaTime);
	if (npcStateComp->state == SLEEP) sleep(position, npcStateComp);
	if (npcStateComp->state == COMBAT) combat(position, combatComp, npcStateComp, deltaTime);
}

void StateMachine::patrol(Vector2d* position, MovementComponent* moveComp, NPCStateComponent * npcStateComp, float deltaTime)
{
	//std::cout << "Patrolling" << std::endl;
	if (isDestinationWithinRange(position, playerPos, npcStateComp->detectionRange))
		notify(npcStateComp, PLAYER_DETECTED);
	else if (!isDestinationWithinRange(position, &npcStateComp->destination, minRangeFromDestination))
		movementManager->moveToDestination(position, moveComp->walkSpeed * 0.5, &npcStateComp->destination, deltaTime);
	else
		notify(npcStateComp, DESTINATION_REACHED);
}

void StateMachine::chase(Vector2d* position, MovementComponent* moveComp, NPCStateComponent * npcStateComp, float deltaTime)
{
	//std::cout << "Chasing" << std::endl;
	if (isDestinationWithinRange(position, playerPos, npcStateComp->combatRange))
		notify(npcStateComp, PLAYER_REACHED);
	else if (isDestinationWithinRange(position, playerPos, npcStateComp->detectionRange))
	{
		npcStateComp->destination = *playerPos;
		movementManager->moveToDestination(position, moveComp->runSpeed * 0.75, &npcStateComp->destination, deltaTime);
	}
	else
		notify(npcStateComp, PLAYER_LOST);
}

void StateMachine::sleep(Vector2d* position, NPCStateComponent * npcStateComp)
{
	// Idle
}

void StateMachine::learn(Vector2d* position, NPCStateComponent * npcStateComp)
{
	//std::cout << "Learning" << std::endl;
	while (!npcStateComp->notificationQueue.empty())
	{
		int notification = npcStateComp->notificationQueue.front();
		npcStateComp->notificationQueue.pop();

		switch (notification)
		{
		case PLAYER_DETECTED:
			npcStateComp->state = CHASE;
			break;
		case PLAYER_REACHED:
			npcStateComp->state = COMBAT;
			break;

			// The cases below alll share the same procedure!
		case PLAYER_LOST:
			npcStateComp->destination = generateDestination(position, npcStateComp);
			npcStateComp->state = PATROL;
			break;
		case OBSTACLE_DETECTED:
			npcStateComp->destination = generateDestination(position, npcStateComp);
			npcStateComp->state = PATROL;
			break;
		case DESTINATION_REACHED:
			npcStateComp->destination = generateDestination(position, npcStateComp);
			npcStateComp->state = PATROL;
			break;
		default:
			break;
		}
	}

	if(npcStateComp->state == 0)
		npcStateComp->state = defaultState;
}

void StateMachine::combat(Vector2d* position, CombatComponent * moveComp, NPCStateComponent * npcStateComp, float deltaTime)
{
	//std::cout << "Fighting" << std::endl;
	if (isDestinationWithinRange(position, playerPos, npcStateComp->combatRange))
	{
		//Do combat
	}
	else if (isDestinationWithinRange(position, playerPos, npcStateComp->detectionRange))
		notify(npcStateComp, PLAYER_DETECTED);
	else
		notify(npcStateComp, PLAYER_LOST);
}
