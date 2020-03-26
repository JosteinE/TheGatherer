#pragma once
#include <SFML/Window/Event.hpp>

class InputComponent;
class GameStateComponent;
class GameStateManager;


class InputManager
{
public:
	InputManager();
	~InputManager();

	sf::Vector2i getRelativeMousePosition(InputComponent* inComp, sf::Vector2i point, double camZoom);

	void keyboardPressed(GameStateManager* gameStateManager, GameStateComponent* gameStateComp, sf::Event* inEvent);
	void keyboardPressed(GameStateManager* gameStateManager, GameStateComponent* gameStateComp, InputComponent* inComp, sf::Event* inEvent);
	void keyboardReleased(InputComponent* inComp, sf::Event* inEvent);
	void mousePressed(GameStateManager* gameStateManager, GameStateComponent* gameStateComp, sf::Event* inEvent, InputComponent* inComp);
	void mousePressed(GameStateManager* gameStateManager, GameStateComponent* gameStateComp, sf::Event* inEvent);
	void mouseReleased(InputComponent* inComp, sf::Event* inEvent);
	int mouseWheel(InputComponent* inComp, sf::Event* inEvent);

private:
	void buttonEscape(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
	void buttonB(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
	void buttonE(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
	void buttonN(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);

	// Arrow keys
	void buttonUp(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
	void buttonLeft(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
	void buttonDown(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
	void buttonRight(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);

	void buttonEnter(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);

	// Mouse
	void buttonLM(GameStateManager* gameStateManager, GameStateComponent* gameStateComp, sf::Event* inEvent);
	void buttonRM(GameStateManager* gameStateManager, GameStateComponent* gameStateComp, sf::Event* inEvent);
};

