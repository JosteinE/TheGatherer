#pragma once
#include "ItemComponent.h"
struct ToolComponent : ItemComponent
{
	unsigned int toolTier;
	unsigned int toolPower;
	unsigned int toolSpeed;
	unsigned int toolReach = 1;
};