#pragma once
#include <SFML/Window/Event.hpp>

class InputComponent;

class InputManager
{
public:
	InputManager();
	~InputManager();

	void registerKeyboardInput(InputComponent* inComp, sf::Event* inEvent);
	void registerMouseInput(InputComponent* inComp, sf::Event* inEvent);
};

