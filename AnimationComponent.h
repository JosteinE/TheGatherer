#pragma once
#include <iostream>
#include "Vector2d.h"

struct AnimationComponent
{
	Vector2d frameSize; // Size of the individual frames or sprites in a sprite sheet
	unsigned int numLayers;
	unsigned int numFrames;
	unsigned int currrentFrame;
	unsigned int currrentLayer;
};