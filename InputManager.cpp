#include "InputManager.h"
#include "InputComponent.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "GameStateComponent.h"
#include "GameStateManager.h"

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

void InputManager::keyboardReleased(InputComponent * inComp, sf::Event* inEvent)
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
	case sf::Keyboard::I:
		inComp->keyI = false;
		break;
	case sf::Keyboard::B:
		inComp->keyB = false;
		break;
	case sf::Keyboard::N:
		inComp->keyN = false;
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
	case sf::Keyboard::Up:
		inComp->keyUpArrow = false;
		break;
	case sf::Keyboard::Left:
		inComp->keyLeftArrow = false;
		break;
	case sf::Keyboard::Down:
		inComp->keyDownArrow = false;
		break;
	case sf::Keyboard::Right:
		inComp->keyRightArrow = false;
		break;
	default:
		break;
	}
}

void InputManager::keyboardPressed(GameStateManager* gameStateManager, GameStateComponent* gameStateComp, InputComponent* inComp, sf::Event* inEvent)
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
		buttonE(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::I:
		inComp->keyI = true;
		break;
	case sf::Keyboard::B:
		inComp->keyB = true;
		break;
	case sf::Keyboard::N:
		inComp->keyN = true;
		buttonN(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::LShift:
		inComp->keyLShift = true;
		break;
	case sf::Keyboard::Space:
		inComp->keySpace = true;
		break;
	case sf::Keyboard::Escape:
		inComp->keyESC = true;
		buttonEscape(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Up:
		inComp->keyUpArrow = true;
		buttonUp(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Left:
		inComp->keyLeftArrow = true;
		buttonLeft(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Down:
		inComp->keyDownArrow = true;
		buttonDown(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Right:
		inComp->keyRightArrow = true;
		buttonRight(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Enter:
		buttonEnter(gameStateManager, gameStateComp);
		break;
	default:
		break;
	}
}

void InputManager::mousePressed(GameStateManager * gameStateManager, GameStateComponent * gameStateComp, sf::Event * inEvent, InputComponent * inComp)
{
	switch (inEvent->mouseButton.button)
	{
	case sf::Mouse::Left:
		inComp->LMB = true;
		inComp->mouseX = inEvent->mouseButton.x;
		inComp->mouseY = inEvent->mouseButton.y;
		buttonLM(gameStateManager, gameStateComp, inEvent);
		break;
	case sf::Mouse::Right:
		inComp->RMB = true;
		buttonRM(gameStateManager, gameStateComp, inEvent);
		break;
	default:
		break;
	}
}

void InputManager::mousePressed(GameStateManager * gameStateManager, GameStateComponent * gameStateComp, sf::Event * inEvent)
{
	switch (inEvent->mouseButton.button)
	{
	case sf::Mouse::Left:
		buttonLM(gameStateManager, gameStateComp, inEvent);
		break;
	case sf::Mouse::Right:
		buttonRM(gameStateManager, gameStateComp, inEvent);
		break;
	default:
		break;
	}
}

void InputManager::mouseReleased(InputComponent * inComp, sf::Event * inEvent)
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

int InputManager::mouseWheel(InputComponent * inComp, sf::Event * inEvent)
{
	switch (inEvent->mouseWheelScroll.wheel)
	{
	case sf::Mouse::VerticalWheel:
		return -inEvent->mouseWheelScroll.delta;
	default:
		return 0;
	}
}

void InputManager::keyboardPressed(GameStateManager * gameStateManager, GameStateComponent * gameStateComp, sf::Event * inEvent)
{
	switch (inEvent->key.code)
	{
	case sf::Keyboard::N:
		buttonN(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Escape:
		buttonEscape(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Up:
		buttonUp(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Left:
		buttonLeft(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Down:
		buttonDown(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Right:
		buttonRight(gameStateManager, gameStateComp);
		break;
	case sf::Keyboard::Enter:
		buttonEnter(gameStateManager, gameStateComp);
		break;
	default:
		break;
	}
}

void InputManager::buttonEscape(GameStateManager* gameStateManager, GameStateComponent* gameStateComp)
{
	if (gameStateComp->currentState == STATE_PLAY_MENU)
		gameStateManager->setState(gameStateComp, STATE_PLAY);
	else if (gameStateComp->currentState == STATE_PLAY)
		gameStateManager->setState(gameStateComp, STATE_RESTART_GAME);
	else if (gameStateComp->currentState == STATE_MAIN_MENU)
		gameStateManager->setState(gameStateComp, STATE_CLOSE_GAME);
}

void InputManager::buttonB(GameStateManager* gameStateManager, GameStateComponent* gameStateComp)
{
}

void InputManager::buttonE(GameStateManager* gameStateManager, GameStateComponent* gameStateComp)
{
	if (gameStateComp->currentState == STATE_PLAY)
		gameStateManager->setState(gameStateComp, STATE_PLAY_MENU, CRAFTING_MENU);
	else if (gameStateComp->currentState == STATE_PLAY_MENU)
		gameStateManager->setState(gameStateComp, STATE_PLAY, UNDEFINED_MENU);
}

void InputManager::buttonN(GameStateManager* gameStateManager, GameStateComponent* gameStateComp)
{
	if (gameStateComp->currentState == STATE_MAIN_MENU)
		gameStateManager->setState(gameStateComp, STATE_NEW_GAME);
}

void InputManager::buttonUp(GameStateManager * gameStateManager, GameStateComponent * gameStateComp)
{
}

void InputManager::buttonLeft(GameStateManager * gameStateManager, GameStateComponent * gameStateComp)
{
	if (gameStateComp->currentState == STATE_MAIN_MENU || gameStateComp->currentState == STATE_PLAY_MENU)
	{
		gameStateManager->previousButton();
	}
}

void InputManager::buttonDown(GameStateManager * gameStateManager, GameStateComponent * gameStateComp)
{
}

void InputManager::buttonRight(GameStateManager * gameStateManager, GameStateComponent * gameStateComp)
{
	if (gameStateComp->currentState == STATE_MAIN_MENU || gameStateComp->currentState == STATE_PLAY_MENU)
	{
		gameStateManager->nextButton();
	}
}

void InputManager::buttonEnter(GameStateManager * gameStateManager, GameStateComponent * gameStateComp)
{
	gameStateManager->selectButton(gameStateComp);
}

void InputManager::buttonLM(GameStateManager * gameStateManager, GameStateComponent * gameStateComp, sf::Event* inEvent)
{
}

void InputManager::buttonRM(GameStateManager * gameStateManager, GameStateComponent * gameStateComp, sf::Event* inEvent)
{
}
