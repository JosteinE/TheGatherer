#pragma once
#include "Vector2d.h"
struct GeneralDataComponent
{
	unsigned int ID = 0;
	unsigned int layer = 0;
	std::string name = "Entity";
	Vector2d position;
};