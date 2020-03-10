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
	void mousePressed(InputComponent* inComp, sf::Event* inEvent);
	void mouseReleased(InputComponent* inComp, sf::Event* inEvent);
	int mouseWheel(InputComponent* inComp, sf::Event* inEvent);

private:
	void buttonEscape(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
	void buttonB(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
	void buttonE(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
	void buttonN(GameStateManager* gameStateManager, GameStateComponent* gameStateComp);
};

