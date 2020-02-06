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

sf::Vector2i InputManager::getRelativeMousePosition(InputComponent* inComp, sf::Vector2i point, double camZoom)
{
	return sf::Vector2i((inComp->mouseX - point.x) * camZoom, (inComp->mouseY - point.y) * camZoom);
}

void InputManager::KeyboardReleased(InputComponent * inComp, sf::Event* inEvent)
{
	switch (inEvent->key.code)
	{
	case sf::Keyboard::W:
		inComp->keyW = false;
		break;
	case sf::Keyboard::A:
		inComp->keyA = false;
		break;
	case sf::Keyboard::S:
		inComp->keyS = false;
		break;
	case sf::Keyboard::D:
		inComp->keyD = false;
		break;
	case sf::Keyboard::E:
		inComp->keyE = false;
		break;
	case sf::Keyboard::B:
		inComp->keyB = false;
		break;
	case sf::Keyboard::LShift:
		inComp->keyLShift = false;
		break;
	case sf::Keyboard::Space:
		inComp->keySpace = false;
		break;
	case sf::Keyboard::Escape:
		inComp->keyESC = false;
		break;
	default:
		break;
	}
}

void InputManager::KeyboardPressed(InputComponent* inComp, sf::Event* inEvent)
{
	switch (inEvent->key.code)
	{
	case sf::Keyboard::W:
		inComp->keyW = true;
		break;
	case sf::Keyboard::A:
		inComp->keyA = true;
		break;
	case sf::Keyboard::S:
		inComp->keyS = true;
		break;
	case sf::Keyboard::D:
		inComp->keyD = true;
		break;
	case sf::Keyboard::E:
		inComp->keyE = true;
		break;
	case sf::Keyboard::B:
		inComp->keyB = true;
		break;
	case sf::Keyboard::LShift:
		inComp->keyLShift = true;
		break;
	case sf::Keyboard::Space:
		inComp->keySpace = true;
		break;
	case sf::Keyboard::Escape:
		inComp->keyESC = true;
		break;
	default:
		break;
	}
}

void InputManager::MousePressed(InputComponent * inComp, sf::Event * inEvent)
{
	switch (inEvent->mouseButton.button)
	{
	case sf::Mouse::Left:
		inComp->LMB = true;
		inComp->mouseX = inEvent->mouseButton.x;
		inComp->mouseY = inEvent->mouseButton.y;
		break;
	case sf::Mouse::Right:
		inComp->RMB = true;
		break;
	default:
		break;
	}
}

void InputManager::MouseReleased(InputComponent * inComp, sf::Event * inEvent)
{
	switch (inEvent->mouseButton.button)
	{
	case sf::Mouse::Left:
		inComp->LMB = false;
		break;
	case sf::Mouse::Right:
		inComp->RMB = false;
		break;
	default:
		break;
	}
}

int InputManager::MouseWheel(InputComponent * inComp, sf::Event * inEvent)
{
	switch (inEvent->mouseWheelScroll.wheel)
	{
	case sf::Mouse::VerticalWheel:
		return -inEvent->mouseWheelScroll.delta;
	default:
		return 0;
	}
}
