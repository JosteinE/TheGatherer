#pragma once
#include <queue>
#include "Vector2d.h"

struct NPCStateComponent
{
	int emotion = 0;
	int state = 0;
	int detectionRange = 75;
	int combatRange = 5;
	std::queue<int> notificationQueue;
	Vector2d destination;
};