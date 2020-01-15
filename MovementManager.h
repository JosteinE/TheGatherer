#pragma once
#include "Vector2d.h"

struct MovementComponent;
struct InputComponent;

class MovementManager
{
public:
	MovementManager();
	~MovementManager();

	void moveByInput(Vector2d* entityPos, MovementComponent* moveComp, InputComponent* inputComp, float deltaTime);
};

