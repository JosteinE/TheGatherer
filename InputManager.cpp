#include "InputManager.h"
#include "InputComponent.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::manageInput(InputComponent* inComp)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		inComp->keyW = true;
		std::cout << "lol fail" << std::endl;
	}
	else
	{
		inComp->keyW = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		inComp->keyA = true;
	}
	else
	{
		inComp->keyA = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		inComp->keyS = true;
	}
	else
	{
		inComp->keyS = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		inComp->keyD = true;
	}
	else
	{
		inComp->keyD = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		inComp->keySpace = true;
	}
	else
	{
		inComp->keySpace = false;
	}
}
