#pragma once
#include "Vector2d.h"
#include "MovementManager.h"

enum NPCemotions { FRIENDLY, NEUTRAL, HOSTILE };
enum NPCstates { LEARN, PATROL, CHASE, COMBAT, SLEEP};
enum NPCevents { ITEM_TAKEN, OBSTACLE_DETECTED, DESTINATION_REACHED, PLAYER_DETECTED, PLAYER_REACHED, PLAYER_LOST };

class NPCStateComponent;
class MovementComponent;
class CombatComponent;

class StateMachine
{
private:
	MovementManager* movementManager{ nullptr };
	int maxDestinationDistance = 50;
	int minRangeFromDestination = 1;
	int defaultState = PATROL; // LEARN here will cause an infinite loop. 
	Vector2d* playerPos{ nullptr };

public:
	StateMachine(MovementManager* inMovementManager, Vector2d* inPlayerPos);
	~StateMachine();

	void runMachine(float deltaTime, Vector2d* position, MovementComponent* moveComp, NPCStateComponent* npcStateComp, CombatComponent* combatComp = nullptr);

private:
	void notify(NPCStateComponent* npcStateComp, int notification);

	void sleep(Vector2d* position, NPCStateComponent* npcStateComp);
	void learn(Vector2d* position, NPCStateComponent* npcStateComp);
	void patrol(Vector2d* position, MovementComponent* moveComp, NPCStateComponent* npcStateComp, float deltaTime);
	void chase(Vector2d* position, MovementComponent* moveComp, NPCStateComponent* npcStateComp, float deltaTime);
	void combat(Vector2d* position, CombatComponent* moveComp, NPCStateComponent* npcStateComp, float deltaTime);

	Vector2d generateDestination(Vector2d* position, NPCStateComponent* npcStateComp, Vector2d* areaMin = nullptr, Vector2d* areaMax = nullptr);
	bool isDestinationWithinRange(Vector2d* position, Vector2d* destination, int maxRange);
};

