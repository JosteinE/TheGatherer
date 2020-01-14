#pragma once
class InputComponent;
class InputManager
{
public:
	InputManager();
	~InputManager();

	void manageInput(InputComponent* inComp);
};

