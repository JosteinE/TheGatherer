#pragma once
#include "Vector2d.h"
struct CollisionComponent
{
	float colExtentLeft = 4;
	float colExtentRight = 4;
	float colExtentUp = 0;
	float colExtentDown = 8;
	bool isColliding = false;
};