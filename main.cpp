#include "RenderWindow.h"

#include "GameStateComponent.h"
#include "GameStateManager.h"

/* Husk å kopier de nødvendige DLL filene inn i mappen .exe filen ligger (prosjektmappa > x64 > debug/release).
* Disse kan hentes fra SFML > Bin mappen.
* openal32.dll må være der, usikker med de andre. 
* https://www.sfml-dev.org/tutorials/2.5/start-vc.php
*/

/* TODAYS PLAN
*	States: Game & Menu(s)
*	Night mode on a timer
*	Player HP, fail state, combat?
*	Multiple lights
*/

void registerEvent(GameStateManager* gameStateManager, GameStateComponent* gameStateComp, RenderWindow* inRenderWindow);

int main()
{
	// Render window
	RenderWindow mRenderWindow;

	// Game State
	GameStateComponent mStateComp;
	GameStateManager mStateManager(&mRenderWindow.mWindow->getSize());
	mStateManager.setState(&mStateComp, STATE_NEW_GAME); // Should be STATE_MAIN_MENU or STATE_NEW_GAME by default!

	//Delta time
	sf::Clock deltaClock;

	//Render loop
	while (mRenderWindow.mWindow->isOpen())
	{
		registerEvent(&mStateManager, &mStateComp, &mRenderWindow);

		//sf::Time dt = deltaClock.restart();

		mStateManager.runState(&mRenderWindow, &mStateComp, deltaClock.restart().asSeconds());
		mRenderWindow.mWindow->display();
	}

	return 0;
}

void registerEvent(GameStateManager* gameStateManager, GameStateComponent* gameStateComp, RenderWindow* inRenderWindow)
{
	sf::Event event;

	if (inRenderWindow->mPlayer == nullptr)
	{
		while (inRenderWindow->mWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				inRenderWindow->mWindow->close();
				break;
			case sf::Event::KeyPressed:
				inRenderWindow->mInputManager.keyboardPressed(gameStateManager, gameStateComp, &event);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		while (inRenderWindow->mWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				inRenderWindow->mWindow->close();
				break;
			case sf::Event::KeyPressed:
				inRenderWindow->mInputManager.keyboardPressed(gameStateManager, gameStateComp, inRenderWindow->mPlayer->mInputComponent, &event);
				break;
			case sf::Event::KeyReleased:
				inRenderWindow->mInputManager.keyboardReleased(inRenderWindow->mPlayer->mInputComponent, &event);
				break;
			case sf::Event::MouseButtonPressed:
				inRenderWindow->mInputManager.mousePressed(gameStateManager, gameStateComp, &event, inRenderWindow->mPlayer->mInputComponent);
				break;
			case sf::Event::MouseButtonReleased:
				inRenderWindow->mInputManager.mouseReleased(inRenderWindow->mPlayer->mInputComponent, &event);
				break;
			case sf::Event::MouseWheelScrolled:
				inRenderWindow->zoomCamera(inRenderWindow->mInputManager.mouseWheel(inRenderWindow->mPlayer->mInputComponent, &event));
				break;
			default:
				break;
			}
		}
	}
}