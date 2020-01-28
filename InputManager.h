#pragma once
#include <SFML/Window/Event.hpp>

class InputComponent;

class InputManager
{
public:
	InputManager();
	~InputManager();

	sf::Vector2i getRelativeMousePosition(InputComponent* inComp, sf::Vector2i point, double camZoom);

	void KeyboardPressed(InputComponent* inComp, sf::Event* inEvent);
	void KeyboardReleased(InputComponent* inComp, sf::Event* inEvent);
	void MousePressed(InputComponent* inComp, sf::Event* inEvent);
	void MouseReleased(InputComponent* inComp, sf::Event* inEvent);
};

