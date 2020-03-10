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
	GameStateManager();
	~GameStateManager();

	void runState(RenderWindow* inRenderWindow, GameStateComponent* inComp, float deltaTime);
	void setState(GameStateComponent* inComp, int newState, int newMenu = -1);
	void setMenu(GameStateComponent* inComp, int newMenu);

private:
	void initNewGame(RenderWindow* inRenderWindow);

	void mainMenuState(RenderWindow* inRenderWindow);
	void playState(RenderWindow* inRenderWindow, float deltaTime);
	void playMenuState(RenderWindow* inRenderWindow, GameStateComponent* inComp, float deltaTime);
	void deadState(RenderWindow* inRenderWindow, float deltaTime);

	void drawMenu(RenderWindow* inRenderWindow, int menu, Vector2d* playerPos = nullptr);
};