#pragma once
#include <iostream>
#include "Vector2d.h"

struct SpawnerComponent
{
	int section;
	int numToSpawn;
	Vector2d spawnPoint;
	int npcMaxRange = 100;
	std::string texturePath{ "Assets/Textures/pCharSheet.png" };
};