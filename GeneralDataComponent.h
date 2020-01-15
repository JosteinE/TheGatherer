#pragma once
#include "Vector2d.h"
struct GeneralDataComponent
{
	unsigned int ID = 0;
	std::string name = "Entity";
	Vector2d position{ 0.f, 0.f };
};