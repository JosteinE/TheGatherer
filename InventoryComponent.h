#pragma once
#include "ToolComponent.h"
struct InventoryComponent
{
	unsigned int currentBarSlot;
	ToolComponent itemBar[3];
	ItemComponent inventory[2]; // Currently just 2 for wood and minerals
};