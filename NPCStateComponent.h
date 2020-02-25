#pragma once
#include <queue>
#include "Vector2d.h"

struct NPCStateComponent
{
	int emotion = 0;
	int state = 0;
	int detectionRange = 75;
	int combatRange = 5;
	float patrolRange = 0.33f; // % range from the restricted area center to its edges. 1 = no restrictions within the area, 0% = bound to the areas center. 
	std::queue<int> notificationQueue;
	bool areaRestricted{ false };
	Vector2d restrictedAreaMin;
	Vector2d restrictedAreaMax;
	Vector2d destination;
};