#pragma once
#include "ToolComponent.h"
struct InventoryComponent
{
	unsigned int numMinerals = 0;
	unsigned int numWood = 0;
	unsigned int currentBarSlot = 0;
	ToolComponent itemBar[3];
	ItemComponent inventory[2]; // Currently just 2 for wood and minerals
};