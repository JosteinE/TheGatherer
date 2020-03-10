#pragma once

enum GAME_STATES
{
	STATE_UNDEFINED,
	STATE_MAIN_MENU,
	STATE_PLAY,
	STATE_PLAY_MENU,
	STATE_DEAD,
	STATE_CLOSE_GAME,
	STATE_RESTART_GAME,
	STATE_NEW_GAME,
};

struct GameStateComponent
{
	unsigned int currentState = 0;
	unsigned int currentMenu = 0;
};