#include "GameStateManager.h"
#include "GameStateComponent.h"
#include "RenderWindow.h"
#include "GeneralDataComponent.h"
#include <SFML/Graphics/RenderTarget.hpp>


GameStateManager::GameStateManager(sf::Vector2u* screenSize)
{
	mMenu.setScreenSize(screenSize);
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
	case STATE_CLOSE_GAME:
		inRenderWindow->mWindow->close(); break;
	case STATE_RESTART_GAME:
		inRenderWindow->resetGame();
		setState(inComp, STATE_MAIN_MENU, MAIN_MENU); break;
	case STATE_NEW_GAME:
		inRenderWindow->initNewGame();
		setState(inComp, STATE_PLAY); break;
	default:
		break;
	}
}

void GameStateManager::setState(GameStateComponent * inComp, int newState, int newMenu)
{
	std::cout << "New state: " << newState << std::endl;
	inComp->currentState = newState;
	if (newMenu != -1)
		setMenu(inComp, newMenu);
}

void GameStateManager::setMenu(GameStateComponent * inComp, int newMenu)
{
	std::cout << "New menu: " << newMenu << std::endl;
	inComp->currentMenu = newMenu;
}

void GameStateManager::initNewGame(RenderWindow * inRenderWindow)
{
	inRenderWindow->initNewGame();
}

void GameStateManager::mainMenuState(RenderWindow* inRenderWindow)
{
	drawMenu(inRenderWindow, MAIN_MENU);
}

void GameStateManager::playState(RenderWindow* inRenderWindow, float deltaTime)
{
	secondTracker += deltaTime;

	if (secondTracker >= 1.f)
	{
		inRenderWindow->addSeconds(3600, deltaTime);
		secondTracker = 0;
	}

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
