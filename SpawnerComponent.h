#pragma once
#include <iostream>
#include "Vector2d.h"

struct SpawnerComponent
{
	int section;
	int numToSpawn;
	Vector2d spawnAreaMin;
	Vector2d spawnAreaMax;
	const std::string texturePath{ "Assets/Textures/pCharSheet.png" };
};