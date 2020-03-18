#pragma once
#include "Menu.h"

struct GameStateComponent;
class RenderWindow;

class GameStateManager
{
private:
	Menu mMenu;
	float secondTracker = 0.f;
public:
	GameStateManager(sf::Vector2u* screenSize);
	~GameStateManager();

	void runState(RenderWindow* inRenderWindow, GameStateComponent* inComp, float deltaTime);
	void setState(GameStateComponent* inComp, int newState, int newMenu = -1);

	void previousButton();
	void nextButton();
	void selectButton(GameStateComponent * inComp);

private:
	void initNewGame(RenderWindow* inRenderWindow);

	void mainMenuState(RenderWindow* inRenderWindow);
	void playState(RenderWindow* inRenderWindow, float deltaTime);
	void playPlacementState(RenderWindow* inRenderWindow, float deltaTime);
	void playMenuState(RenderWindow* inRenderWindow, GameStateComponent* inComp, float deltaTime);
	void deadState(RenderWindow* inRenderWindow, float deltaTime);

	void setMenu(GameStateComponent* inComp, int newMenu);
	void drawMenu(RenderWindow* inRenderWindow, int menu, Vector2d* playerPos = nullptr);
};