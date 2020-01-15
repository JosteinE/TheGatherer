#pragma once
class InputComponent;
class InputManager
{
public:
	InputManager();
	~InputManager();

	void registerInput(InputComponent* inComp);
};

