#include "GameStateManager.h"
#include "GameStateComponent.h"
#include "RenderWindow.h"
#include "GeneralDataComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>


GameStateManager::GameStateManager()
{
}


GameStateManager::~GameStateManager()
{
}

void GameStateManager::runState(RenderWindow* inRenderWindow, GameStateComponent * inComp, float deltaTime)
{
	switch (inComp->currentState)
	{
	case STATE_MAIN_MENU:
		mainMenuState(inRenderWindow); break;
	case STATE_PLAY:
		playState(inRenderWindow, deltaTime); break;
	case STATE_PLAY_MENU:
		playMenuState(inRenderWindow, inComp, deltaTime); break;
	case STATE_DEAD:
		deadState(inRenderWindow, deltaTime); break;
	default:
		break;
	}
}

void GameStateManager::setState(GameStateComponent * inComp, int newState)
{
	inComp->currentState = newState;
}

void GameStateManager::mainMenuState(RenderWindow* inRenderWindow)
{
	drawMenu(inRenderWindow, MAIN_MENU);
}

void GameStateManager::playState(RenderWindow* inRenderWindow, float deltaTime)
{
	inRenderWindow->tick(deltaTime);
}

void GameStateManager::playMenuState(RenderWindow* inRenderWindow, GameStateComponent* inComp, float deltaTime)
{
	playState(inRenderWindow, deltaTime);
	drawMenu(inRenderWindow, inComp->currentMenu, &inRenderWindow->mPlayer->mGeneralDataComponent->position);
}

void GameStateManager::deadState(RenderWindow* inRenderWindow, float deltaTime)
{
	// Maybe something here?
	playState(inRenderWindow, deltaTime);
}

void GameStateManager::drawMenu(RenderWindow * inRenderWindow, int menu, Vector2d * playerPos)
{
	if (mMenu.menuConstructed != menu)
		mMenu.constructMenu(menu);

	mMenu.draw(*inRenderWindow->mWindow, playerPos);
}
