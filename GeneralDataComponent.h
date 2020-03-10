#pragma once
#include "Vector2d.h"
struct GeneralDataComponent
{
	unsigned int section = 0;
	//unsigned int ID = 0;
	unsigned int type = 0; // item, character, etc..
	unsigned int layer = 0;
	std::string name = "Entity";

	Vector2d* origin{ nullptr }; // Only relevant if isChild = true
	Vector2d position{ 0, 0 };
	bool tempEntity{ false };
	bool isChild{ false };
};