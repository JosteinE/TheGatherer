#pragma once
#include <SFML/System/Vector2.hpp>

struct MovementComponent;
struct InputComponent;

class MovementManager
{
public:
	MovementManager();
	~MovementManager();

	void moveByInput(sf::Vector2f* entityPos, MovementComponent* moveComp, InputComponent* inputComp, float deltaTime);
};

