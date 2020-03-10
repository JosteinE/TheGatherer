#pragma once
#include "Menu.h"

enum GAME_STATES
{
	STATE_UNDEFINED,
	STATE_MAIN_MENU,
	STATE_PLAY,
	STATE_PLAY_MENU,
	STATE_DEAD
};

struct GameStateComponent;
class RenderWindow;

class GameStateManager
{
private:
	Menu mMenu;
public:
	GameStateManager();
	~GameStateManager();

	void runState(RenderWindow* inRenderWindow, GameStateComponent* inComp, float deltaTime);
	void setState(GameStateComponent* inComp, int newState);

private:
	void mainMenuState(RenderWindow* inRenderWindow);
	void playState(RenderWindow* inRenderWindow, float deltaTime);
	void playMenuState(RenderWindow* inRenderWindow, GameStateComponent* inComp, float deltaTime);
	void deadState(RenderWindow* inRenderWindow, float deltaTime);

	void drawMenu(RenderWindow* inRenderWindow, int menu, Vector2d* playerPos = nullptr);
};